#include<iostream>
#include "./gdal/gdal_priv.h"
#pragma comment(lib, "gdal_i.lib")

using namespace std;

int main()
{
	//输入图像
	GDALDataset* poSrcDS1;
	GDALDataset* poSrcDS2;
	//输出图像
	GDALDataset* poDstDS;
	//输入图像的宽度和高度
	int imgXlen1, imgYlen1;
	int imgXlen2, imgYlen2;
	//输入图像路径
	const char* srcPath1 = "space.jpg";
	const char* srcPath2 = "superman.jpg";
	//输出图像的路径
	const char* dstPath = "output.jpg";
	//图像内存存储
	GByte *buffTmp1[3];
	GByte *buffTmp2[3];
	//图像波段数
	int bandNum;
	//所抠出图像的像素rgb的上下限
	int r[2] = {10, 160}, g[2] = {100, 220}, b[2] = {10, 110};

	//注册驱动
	GDALAllRegister();

	//打开图像
	poSrcDS1 = (GDALDataset*)GDALOpenShared(srcPath1, GA_ReadOnly);
	poSrcDS2 = (GDALDataset*)GDALOpenShared(srcPath2, GA_ReadOnly);

	//获取图像宽度，高度，波段数
	imgXlen1 = poSrcDS1->GetRasterXSize();
	imgYlen1 = poSrcDS1->GetRasterYSize();
	bandNum = poSrcDS1->GetRasterCount();
	imgXlen2 = poSrcDS2->GetRasterXSize();
	imgYlen2 = poSrcDS2->GetRasterYSize();

	//输出获取的结果
	cout << "IMG " << srcPath1 << " X Length:" << imgXlen1;
	cout << ", Y Length:" << imgYlen1 << endl;
	cout << "IMG " << srcPath2 << " X Length:" << imgXlen2;
	cout << ", Y Length:" << imgYlen2 << endl;
	cout << "Band Number:" << bandNum << endl;

	//根据图像的宽度和高度分配内存
	for (int i = 0; i < 3; i++) {
		buffTmp1[i] = (GByte*)CPLMalloc(imgXlen1 * imgYlen1 * sizeof(GByte));
		buffTmp2[i] = (GByte*)CPLMalloc(imgXlen2 * imgYlen2 * sizeof(GByte));
	}

	//创建输出图像
	poDstDS = GetGDALDriverManager()->GetDriverByName("GTiff")->Create(
		dstPath, imgXlen1, imgYlen1, bandNum, GDT_Byte, NULL);

	//分波段获取图像像素
	for (int i = 0; i < bandNum; i++) {
		poSrcDS1->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen1, imgYlen1, buffTmp1[i], imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		poSrcDS2->GetRasterBand(i + 1)->RasterIO(GF_Read,
			0, 0, imgXlen2, imgYlen2, buffTmp2[i], imgXlen1, imgYlen1, GDT_Byte, 0, 0);
	}

	//判断像素范围
	for (int i = 0; i < imgYlen2; i++) {
		for (int j = 0; j < imgXlen2; j++) {
			if (buffTmp2[0][i * imgXlen2 + j] <= r[0] || buffTmp2[0][i * imgXlen2 + j] >= r[1] ||
				buffTmp2[1][i * imgXlen2 + j] <= g[0] || buffTmp2[1][i * imgXlen2 + j] >= g[1] ||
				buffTmp2[2][i * imgXlen2 + j] <= b[0] || buffTmp2[2][i * imgXlen2 + j] >= b[1])
				for (int k = 0; k < bandNum; k++) {
					buffTmp1[k][i * imgXlen2 + j] = buffTmp2[k][i * imgXlen2 + j];
				}
		}
	}

	//按波段输出图片
	for (int i = 0; i < bandNum; i++) {
		poDstDS->GetRasterBand(i + 1)->RasterIO(GF_Write,
			0, 0, imgXlen1, imgYlen1, buffTmp1[i], imgXlen1, imgYlen1, GDT_Byte, 0, 0);
		cout << "... ... band " << i << " processing ... ..." << endl;
	}

	//清除内存
	for(int i = 0; i < bandNum; i++) {
		CPLFree(buffTmp1[i]);
		CPLFree(buffTmp2[i]);
	}
	
	//关闭dataset
	GDALClose(poDstDS);
	GDALClose(poSrcDS1);
	GDALClose(poSrcDS2);

	return 0;
}
