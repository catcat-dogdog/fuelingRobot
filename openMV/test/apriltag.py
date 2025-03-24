import sensor, image, time, math, pyb, ustruct

from pyb import UART


sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA) # we run out of memory if the resolution is much bigger...
sensor.skip_frames(30)
sensor.set_auto_gain(False)  # must turn this off to prevent image washout...
sensor.set_auto_whitebal(False)  # must turn this off to prevent image washout...
clock = time.clock()
uart = UART(3, 115200)

# 注意！与find_qrcodes不同，find_apriltags 不需要软件矫正畸变就可以工作。

# 注意，输出的姿态的单位是弧度，可以转换成角度，但是位置的单位是和你的大小有关，需要等比例换算

# f_x 是x的像素为单位的焦距。对于标准的OpenMV，应该等于2.8/3.984*656，这个值是用毫米为单位的焦距除以x方向的感光元件的长度，乘以x方向的感光元件的像素（OV7725）
# f_y 是y的像素为单位的焦距。对于标准的OpenMV，应该等于2.8/2.952*488，这个值是用毫米为单位的焦距除以y方向的感光元件的长度，乘以y方向的感光元件的像素（OV7725）

# c_x 是图像的x中心位置
# c_y 是图像的y中心位置

f_x = (2.8 / 3.984) * 320 # 默认值
f_y = (2.8 / 2.952) * 240 # 默认值
c_x = 320 * 0.5 # 默认值(image.w * 0.5)
c_y = 240 * 0.5 # 默认值(image.h * 0.5)

def degrees(radians):
    return (180 * radians) / math.pi

def sending_data(pos_deg):
    global uart
    if not isinstance(pos_deg, (list, tuple)):
        raise ValueError("pos_deg should be a list or tuple")

    # 将 pos_deg 中的每个元素转换为浮点数
    pos_deg_float = [float(val) for val in pos_deg]

    # 打包数据，起始字节0xb3，pos_deg中的数据，终止字节0x0d和0x0a
    # 使用 'f' 作为格式字符表示浮点数
    data = ustruct.pack('BB' + 'f' * len(pos_deg_float) + 'BB', 0xb3, 0xb3, *pos_deg_float, 0x0d, 0x0a)

    uart.write(data)

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.lens_corr(1.8)
    for tag in img.find_apriltags(fx=f_x, fy=f_y, cx=c_x, cy=c_y): # 默认为TAG36H11
        img.draw_rectangle(tag.rect(), color = (255, 0, 0))
        img.draw_cross(tag.cx(), tag.cy(), color = (0, 255, 0))
        pos_deg_output = (tag.x_translation(), tag.y_translation(), tag.z_translation(),
        degrees(tag.x_rotation()), degrees(tag.y_rotation()), degrees(tag.z_rotation()))
        print_args = pos_deg_output
        # 位置的单位是未知的，旋转的单位是角度
        #print("Tx: %f, Ty %f, Tz %f, Rx %f, Ry %f, Rz %f" % print_args)
        print("FPS %f" % clock.fps())
        sending_data(pos_deg_output)
        time.sleep_ms(1000)
