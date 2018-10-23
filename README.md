# sofware-project
软件工程项目

Project02：编写代码，学会使用CPLMalloc为图像分配内存，并用循环为图像的每个波段赋值上色，用GetRasterBand(i)->RasterIO()轮流输入输出每个波段。代码编译成功并运行后，报错无法获取图像宽度，原因是没有将源图片的名字改为1.jpg，无法获取到图像。修改后，程序成功输出图像至output.tif，能看到output.tif中有一块被涂成白色，有一块被涂成黑色。

Project03:在Project02的基础上进行修改，输入图像变成两个，分别是space.jpg与superman.jpg，设置buffTmp1[3]与buffTmp2[3]用于获取图像的每个波段的像素，先分波段获取图像像素，再逐个判断superman中的像素是否是要抠的图像的像素，若是则将它覆盖到space的像素中，最后再生成目标图像即可。实验中出现过几次错误：第一，对变量i的取值经常弄错，i从0开始时GetRasterBand(i)中的i应加1；第二，清除buffTmp1与buffTmp2数组的内存时应逐个清除；第三，判断条件弄反，导致最后把绿幕加到space中去了，因此不应取判断条件的范围内，而取判断条件的范围之外，得出的图像中，superman的大部分像素都能覆盖到space上。
