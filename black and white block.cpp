#include<iostream>
using namespace std;
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

int main()
{
	//输入图像
	GDALDataset* poSrcDS;
	//输出图像
	GDALDataset* poDstDS;
	//图像的宽度和高度
	int imgXlen, imgYlen;
	//输入图像路径
	char* srcPath = "input.jpg";
	//输出图像的路径
	char* dstPath = "output.tif";
	//图像内存存储
	GByte* buffTmp,*buffTmp2,*buffTmp3;
	//图像波段数
	int i, bandNum;
	//处理点横坐标，处理点纵坐标，处理宽度，处理高度
	int StartX,StartY,tmpXlen,tmpYlen;

	//注册驱动
	GDALAllRegister();
	//打开图像
	poSrcDS = (GDALDataset*)GDALOpenShared(srcPath, GA_ReadOnly);

	//获取图像宽度，高度，波段数
	imgXlen = poSrcDS->GetRasterXSize();
	imgYlen = poSrcDS->GetRasterYSize();
	bandNum = poSrcDS->GetRasterCount();
	//输出获取的结果
	cout << "IMG  X Length:" << imgXlen << endl;
	cout << "IMG  Y Length:" << imgYlen << endl;
	cout << "Band Number:" << bandNum << endl;

	//根据图像的宽度和高度分配内存
    buffTmp = (GByte*) CPLMalloc(imgXlen * imgYlen * sizeof(GByte));
	//创建输出图像
    poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
        dstPath,imgXlen,imgYlen,bandNum,GDT_Byte,NULL);

    /**
        更改特定区域像素
    */
    //设定初始值
    StartX = 60;
    StartY = 60;
    tmpXlen = 50;
    tmpYlen = 55;
    //分配内存
    buffTmp2 = (GByte*) CPLMalloc(tmpXlen * tmpYlen * sizeof(GByte));
    buffTmp3 = (GByte*) CPLMalloc(tmpXlen * tmpYlen * sizeof(GByte));
    //对每个波段赋值255和0，对应纯白和纯黑
    for(int i = 0;i < tmpYlen;i++){
        for(int j = 0;j < tmpXlen;j++){
            buffTmp2[i * tmpXlen + j] = (GByte)255;
            buffTmp3[i * tmpXlen + j] = (GByte)0;
        }
    }
    //一个一个波段输入。一个一个波段输出
	for(int i = 1 ;i <= bandNum;i++){
        poSrcDS->GetRasterBand(i)->RasterIO(GF_Read,
            0,0,imgXlen,imgYlen,buffTmp,imgXlen,imgYlen,GDT_Byte,0,0);
        poDstDS->GetRasterBand(i)->RasterIO(GF_Write,
            0,0,imgXlen,imgYlen,buffTmp,imgXlen,imgYlen,GDT_Byte,0,0);
        //填充黑色方块
        poDstDS->GetRasterBand(i)->RasterIO(GF_Write,
                                          StartX-50,StartY-50,tmpXlen,tmpYlen,buffTmp3,tmpXlen,tmpYlen,GDT_Byte,0,0);
        //填充白色方块
        poDstDS->GetRasterBand(i)->RasterIO(GF_Write,
                                          StartX+50,StartY+50,tmpXlen,tmpYlen,buffTmp2,tmpXlen,tmpYlen,GDT_Byte,0,0);
        printf("... ... band %d processing ... ...\n",i);
	}
    //红色数据写入poDstDS
    poDstDS->GetRasterBand(1)->RasterIO(GF_Write,
                                        StartX,StartY,tmpXlen,tmpYlen,buffTmp2,tmpXlen,tmpYlen,GDT_Byte,0,0);
	//清除内存
    CPLFree(buffTmp);
    CPLFree(buffTmp2);
    CPLFree(buffTmp3);
    //关闭dataset
    GDALClose(poDstDS);
    GDALClose(poSrcDS);
	return 0;
}

