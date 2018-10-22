# sofware-project
软件工程项目
Project02：编写代码，学会使用CPLMalloc为图像分配内存，并用循环为图像的每个波段赋值上色，用GetRasterBand(i)->RasterIO()轮流输入输出每个波段。代码编译成功并运行后，报错无法获取图像宽度，原因是没有将源图片的名字改为1.jpg，无法获取到图像。修改后，程序成功输出图像至output.tif，能看到output.tif中有一块被涂成白色，有一块被涂成黑色。
