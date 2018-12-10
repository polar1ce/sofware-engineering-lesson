
Project06-遥感图像的分块处理

https://github.com/summitgao/SoftwareClass/blob/master/lesson_06.md

将大尺寸图片进行分块处理，融合多光谱图与全色图

源图下载：https://www.jianguoyun.com/p/DWFm_ksQrKKIBhjRkIgB

project06.cpp - 将原图按行分块，块大小为 imgXlen*256

project06-2.cpp - 将原图按正方形分块，大小为256*256

block256x15696(1)(2)(3) - 按行分块的3次试验运行结果，运行时间分别为 72.513s，44.636s，44.447s

block256x256(1)(2)(3) - 正方形分块的3次试验运行结果，运行时间分别为 110.522s，89.031s，88.597s
