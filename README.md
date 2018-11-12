# sofware-project
软件工程课程项目 - Software Engineering Lesson Project

Project01：使用VS2017,软件装在D盘,顺利创建项目遇到预编译头错误，需在项目属性页中设置不使用预编译头,对照着流程敲代码,在定义图像的输入输出路径变量时需在 char* 前添加 const 使其变成常量才能进行初始化,代码抄写完成，向项目文件夹中放入GDAL库相关文件,并将tree.jpg也放入项目文件夹中,编译运行，成功得到res.tif,打开发现与tree.jpg一样.

Project02：编写代码，学会使用CPLMalloc为图像分配内存，并用循环为图像的每个波段赋值上色，用GetRasterBand(i)->RasterIO()轮流输入输出每个波段。代码编译成功并运行后，报错无法获取图像宽度，原因是没有将源图片的名字改为1.jpg，无法获取到图像。修改后，程序成功输出图像至output.tif，能看到output.tif中有一块被涂成白色，有一块被涂成黑色。

Project03:在Project02的基础上进行修改，输入图像变成两个，分别是space.jpg与superman.jpg，设置buffTmp1[3]与buffTmp2[3]用于获取图像的每个波段的像素，先分波段获取图像像素，再逐个判断superman中的像素是否是要抠的图像的像素，若是则将它覆盖到space的像素中，最后再生成目标图像即可。实验中出现过几次错误：第一，对变量i的取值经常弄错，i从0开始时GetRasterBand(i)中的i应加1；第二，清除buffTmp1与buffTmp2数组的内存时应逐个清除；第三，判断条件弄反，导致最后把绿幕加到space中去了，因此不应取判断条件的范围内，而取判断条件的范围之外，得出的图像中，superman的大部分像素都能覆盖到space上。

Project04：
