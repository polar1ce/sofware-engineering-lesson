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
	char* srcPath = "1.jpg";
	//输出图像的路径
	char* dstPath = "output.tif";
	//图像内存存储
	GByte* buffTmp,*buffTmp1,*buffTmp2;
	//图像波段数
	int i, bandNum;
	//处理点横坐标，处理点纵坐标，处理宽度，处理高度
	int StartX1,StartY1,StartX2,StartY2,tmpXlen1,tmpYlen1,tmpXlen2,tmpYlen2;

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
    StartX1 = 300;
    StartY1 = 300;
    tmpXlen1 = 100;
    tmpYlen1 = 50;
    StartX2 = 500;
    StartY2 = 500;
    tmpXlen2 = 50;
    tmpYlen2 = 100;
    //分配内存
    buffTmp1 = (GByte*) CPLMalloc(tmpXlen1 * tmpYlen1 * sizeof(GByte));
    buffTmp2 = (GByte*) CPLMalloc(tmpXlen2 * tmpYlen2 * sizeof(GByte));
    //对每个波段赋值255和0，对应纯白和纯黑
    for(i = 0;i < tmpYlen1;i++){
        for(int j = 0;j < tmpXlen1;j++){
            buffTmp1[i * tmpXlen1 + j] = (GByte)255;
        }
    }
    for(i = 0;i < tmpYlen2;i++){
        for(int j = 0;j < tmpXlen2;j++){
            buffTmp2[i * tmpXlen2 + j] = (GByte)0;
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
                                          StartX1,StartY1,tmpXlen1,tmpYlen1,buffTmp1,tmpXlen1,tmpYlen1,GDT_Byte,0,0);
        //填充白色方块
        poDstDS->GetRasterBand(i)->RasterIO(GF_Write,
                                          StartX2,StartY2,tmpXlen2,tmpYlen2,buffTmp2,tmpXlen2,tmpYlen2,GDT_Byte,0,0);
        printf("... ... band %d processing ... ...\n",i);
	}
/*    //红色数据写入poDstDS
    poDstDS->GetRasterBand(1)->RasterIO(GF_Write,
                                        StartX,StartY,tmpXlen,tmpYlen,buffTmp1,tmpXlen,tmpYlen,GDT_Byte,0,0);
	*/
	//清除内存
    CPLFree(buffTmp);
    CPLFree(buffTmp1);
    CPLFree(buffTmp2);
    //关闭dataset
    GDALClose(poDstDS);
    GDALClose(poSrcDS);
	return 0;
}
//thisisatest
