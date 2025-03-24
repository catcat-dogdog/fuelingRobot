# Untitled - By: wql19 - Sat Jul 6 2024
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

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.lens_corr(1.8)
    for tag in img.find_apriltags(fx=f_x, fy=f_y, cx=c_x, cy=c_y): # 默认为TAG36H11
        img.draw_rectangle(tag.rect(), color = (255, 0, 0))
        img.draw_cross(tag.cx(), tag.cy(), color = (0, 255, 0))

        pos_deg_output = (tag.x_translation(), tag.y_translation(), tag.z_translation(),
        degrees(tag.x_rotation()), degrees(tag.y_rotation()), degrees(tag.z_rotation()))
        print(pos_deg_output)
        print(tag.cx(), tag.cy())
        print("FPS %f" % clock.fps())

        clockwise = 0
        theta = 0
        if (tag.x_translation() < -0.1):
            clockwise = 0 & 0xFF
            theta = int(180*math.atan2(-tag.x_translation(), -tag.z_translation()) / math.pi + 2) & 0xFF
        elif (tag.x_translation() > 0.1):
            clockwise = 1 & 0xFF
            theta = int(180*math.atan2(tag.x_translation(), -tag.z_translation())/math.pi + 2) & 0xFF
        print(clockwise, theta)
        FH = bytearray([0xb3,0xb3,clockwise,theta,0x00,0x5b])
        uart.write(FH)
