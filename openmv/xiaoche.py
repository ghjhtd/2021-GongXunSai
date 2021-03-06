# QRCode Example
#
# This example shows the power of the OpenMV Cam to detect QR Codes
# without needing lens correction.
# P4 - TX
# P5 - RX
# GND

import sensor, image, time, pyb
from pyb import UART

uart = UART(3, 115200)
uart.init(115200, bits=8, parity=None, stop=1)

led_red = pyb.LED(1)
led_green = pyb.LED(2)
led_blue = pyb.LED(3)

serial_data = ""
qr_code = ""
color_code = ""

# 小球的颜色阈值，根据颜色追踪小球
target_color_threshold   = (74, 51, 13, 93, 3, 81)
# 下面的阈值, 可能需要大家手动调节
thresholds = [(28, 77, 36, 82, -35, 85), # 一般情况下的红色阈值(28, 77, 36, 82, -35, 85)
              (19, 98, -9, 107, -100, 112), # 一般情况下的绿色阈值(16, 40, -58, -18, 8, 50)
              (18, 45, -27, 64, -99, -21)] # 一般情况下的蓝色阈值(26, 71, -27, 1, -59, -20)(7, 32, -31, 26, -82, -12)
              #(2, 20, -8, 8, -28, 15), # 一般情况下的黑色阈值
              #(67, 80, -12, 61, -2, 19) # 一般情况下的白色阈值
GRAYSCALE_THRESHOLD = [(70, 100, -52, 59, -44, 55),
                        (37, 9, 8, -62, -29, 20)]#一般情况下的黑色阈值

sensor.reset()
sensor.set_pixformat(sensor.RGB565) # use RGB565.
sensor.set_framesize(sensor.QVGA) # use QQVGA for speed.
#sensor.set_windowing((160,120))
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()

#led off
def led_off():
    global led_red
    global led_green
    global led_blue
    led_red.off()
    led_green.off()
    led_blue.off()

#led
def led_on(which):
    global led_red
    global led_green
    global led_blue
    for i in range(10):
        if which == 1:
            led_red.toggle()
        elif which == 2:
            led_green.toggle()
        elif which == 3:
            led_blue.toggle()
        time.sleep(0.08)

#如果是红色，执行
def doWithRed(img):
    global color_code
    led_on(1)
    if '1' in color_code:
        print("")
    else:
        color_code += '4'

#如果是绿色，执行
def doWithGreen(img):
    global color_code
    led_on(2)
    if '2' in color_code:
        print("")
    else:
        color_code += '5'

#如果是蓝色，执行
def doWithBlue(img):
    global color_code
    led_on(3)
    if '3' in color_code:
        print("")
    else:
        color_code += '6'

#颜色检测返回值与所需执行的函数的映射
colorCodeMapFunc = {
    1:doWithRed,
    2:doWithGreen,
    4:doWithBlue,
}

def compareBlob(blob1, blob2):
    tmp = blob1.pixels() - blob2.pixels()
    if tmp == 0:
        return 0;
    elif tmp > 0:
        return 1;
    elif tmp < 0:
        return -1;

led_on(1) #红灯闪烁表示程序启动
while(True):
    clock.tick()

    img = sensor.snapshot()
    if uart.any():
        #led_on(3)
        serial_data = uart.readline()
        led_off()
        print(serial_data)
    if serial_data == b'q\r\n':
        #检测二维码并将识别内容发送至串口
        for code in img.find_qrcodes():
            img.draw_rectangle(code.rect(), color = 127)
            print('q'+code.payload())
            if code.payload():
                qr_code = 'q' + code.payload() + "\r\n"
                uart.write(qr_code) #send qr code
                qr_code = ""
                serial_data = ""
                led_on(2)
                sensor.set_windowing((160,120))
    elif serial_data == b'c\r\n':
        #检测颜色并将识别内容发送至串口
        bigBlob = None #最大色块
        #roi2 = [40, 78, 96, 43]#检测下面的
        roi2 = [25, 0, 120, 60]

        blobs = img.find_blobs(thresholds,roi = roi2, pixels_threshold=150, area_threshold=150, merge=True)
        blobs_borw = img.find_blobs(GRAYSCALE_THRESHOLD,roi = roi2, pixels_threshold=150, area_threshold=150, merge=True)
        #判断是否有色块检测到
        if blobs:
            bigBlob = blobs[0]
            for blob in blobs:
                #比较当前色块与所记录的最大色块
                if compareBlob(bigBlob, blob) == -1:
                    bigBlob = blob
            #标记识别到的最大色块
            img.draw_rectangle(bigBlob.rect())
            img.draw_cross(bigBlob.cx(), bigBlob.cy())
            #print(bigBlob.code())
            if bigBlob.code() in colorCodeMapFunc:
                colorCodeMapFunc[bigBlob.code()](img)
                color_code = "C" + color_code + "\r\n"
                print(color_code)
                uart.write(color_code)
                color_code = ""
                serial_data = ""
            else:
                print("code not match" + str(bigBlob.code()))

    elif serial_data == b'd\r\n':
        #检测颜色并将识别内容发送至串口
        bigBlob = None #最大色块
        roi2 = [40, 78, 96, 43]#检测下面的
        #roi2 = [25, 0, 120, 60]#检测上面的

        blobs = img.find_blobs(thresholds,roi = roi2, pixels_threshold=150, area_threshold=150, merge=True)
        blobs_borw = img.find_blobs(GRAYSCALE_THRESHOLD,roi = roi2, pixels_threshold=150, area_threshold=150, merge=True)
        #判断是否有色块检测到
        if blobs:
            bigBlob = blobs[0]
            for blob in blobs:
                #比较当前色块与所记录的最大色块
                if compareBlob(bigBlob, blob) == -1:
                    bigBlob = blob
            #标记识别到的最大色块
            img.draw_rectangle(bigBlob.rect())
            img.draw_cross(bigBlob.cx(), bigBlob.cy())
            #print(bigBlob.code())
            if bigBlob.code() in colorCodeMapFunc:
                colorCodeMapFunc[bigBlob.code()](img)
                color_code = "C" + color_code + "\r\n"
                print(color_code)
                uart.write(color_code)
                color_code = ""
                serial_data = ""
            else:
                print("code not match" + str(bigBlob.code()))
