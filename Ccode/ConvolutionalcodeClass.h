#pragma once
#include<QString>
#include<vector>
class ConvolutionalcodeClass       //卷积类，通过其成员函数来实现卷积编解码
{
public:
	QString Encode(QString b);    //卷积编码
	QString rDecode(QString b);   //软判决译码(维特比译码)
	QString yDecode(QString b);   //硬判决译码
};

