#include "ConvolutionalcodeClass.h"

QString ConvolutionalcodeClass::Encode(QString b)   //三个关键函数中的第一个，卷积编码
{
	QString d = "00" + b;   //设置编码器初始状态为全零
	QString c;
	int n = d.size();
	if (n == 2)     //输入为空，则直接返回空串
		return c;
	QChar zero = '0';
	//char16_t固定为16位，可以用来存储UTF-16编码的16位unicode字符
	char16_t z = zero.unicode();   //计算得到'0'的unicode值，方便后续计算
	for (int i = 2; i < n; i++)
	{
		if (d[i].unicode() != z && d[i].unicode() != z + 1) //二进制序列只允许0和1存在
		{
			QString g;
			return g;
		}
		QChar x1 = d[i];
		//与'0'的unicode值相减，即可得到int值0或1，之后再进行模二加运算，得到编码值
		QChar x2 = QChar((d[i].unicode() - z + d[i - 2].unicode() - z) % 2 + z);
		//利用QChar()这一构造函数将unicode值转化为QChar类型，以方便构造QString字符串
		QChar x3 = QChar((d[i].unicode() - z + d[i - 2].unicode() - z + d[i-1].unicode() - z) % 2 + z);
		c.append(x1);  //在末尾添加字符，从而构造编码后的字符串
		c.append(x2);
		c.append(x3);
	}
	return c;
}

int Hammingdistance(QString a, QString b);   //函数声明


QString ConvolutionalcodeClass::rDecode(QString b)     //维特比译码，是一种抗干扰能力很强的译码方法
{
	QString a;
	int n = b.size();
	if (n % 3 != 0)
		return a;
	int k = n / 3;
	QChar zero = '0';
	char16_t z = zero.unicode();

	//状态1的数组(00)
	std::vector<int> w1;       //存储累加的误比特数
	std::vector<QString> s1;   //存储每一步得到的子串
	w1.push_back(0);
	s1.push_back("00");

	//状态2的数组(01)
	std::vector<int> w2;
	std::vector<QString> s2;

	//状态3的数组(10)
	std::vector<int> w3;
	std::vector<QString> s3;

	//状态4的数组(11)
	std::vector<int> w4;
	std::vector<QString> s4;

	for (int i = 0; i < k; i++)
	{
		QString x;
		for (int j = 0; j <= 2; j++)
		{
			if (b[i * 3 + j].unicode() != z && b[i * 3 + j].unicode() != z + 1) //二进制序列只允许0和1存在
			{
				QString g;
				return g;
			}
			x.append(b[i * 3 + j]);
		}
		if (k == 1)           //特判，如果只有3比特，则软硬判决结果一样
		{
			if (x == "111")   //根据三元组的类型直接判断原码
			{
				a = "1";
				return a;
			}
			if (x == QString("000"))
			{
				a = '0';
				return a;
			}
			if (x == QString("011"))
			{
				a = '0';
				return a;
			}
			if (x == QString("100"))
			{
				a = '1';
				return a;
			}
			if (x == QString("001"))
			{
				a = '0';
				return a;
			}
			if (x == QString("110"))
			{
				a = '1';
				return a;
			}
			if (x == QString("101"))
			{
				a = '1';
				return a;
			}
			if (x == QString("010"))
			{
				a = '0';
				return a;
			}
		}
		if (w1.size() != 0)        //计算状态1
		{
			int p = s1[0].size();
			QString y, y1;
			y.push_back("0");   //输入为0
			y.push_back(s1[0].back());
			y.push_back(s1[0][p - 2]);
			QChar x1 = y[0];
			QChar x2 = QChar((y[0].unicode() - z + y[2].unicode() - z) % 2 + z);
			QChar x3 = QChar((y[0].unicode() - z + y[1].unicode() - z + y[2].unicode() - z) % 2 + z);
			y1.append(x1);
			y1.append(x2);
			y1.append(x3);
			int dis0 = Hammingdistance(y1, x);
			int first1 = w1[0] + dis0;
			y = s1[0] + '0';
			w1.push_back(first1);     //00状态输入0依然是00状态
			s1.push_back(y);
			QString k, k1;
			k.push_back("1");   //输入为1
			k.push_back(s1[0].back());
			k.push_back(s1[0][p - 2]);
			QChar x4 = k[0];
			QChar x5 = QChar((k[0].unicode() - z + k[2].unicode() - z) % 2 + z);
			QChar x6 = QChar((k[0].unicode() - z + k[1].unicode() - z + k[2].unicode() - z) % 2 + z);
			k1.append(x4);
			k1.append(x5);
			k1.append(x6);
			int dis1 = Hammingdistance(k1, x);
			int first2 = w1[0] + dis1;
			k = s1[0] + '1';
			w3.push_back(first2);   //00状态输入1跳转到10状态
			s3.push_back(k);
			auto it = w1.begin();
			auto it1 = s1.begin();
			w1.erase(it);           //将原来的值清除，保证其中的元素不超过3个
			s1.erase(it1);
		}

		if (i == 0)
			continue;

		if (w2.size() != 0 && i != 1)    //计算状态2
		{
			int p = s2[0].size();
			QString y, y1;
			y.push_back("0");   //输入为0
			y.push_back(s2[0].back());
			y.push_back(s2[0][p - 2]);
			QChar x1 = y[0];
			QChar x2 = QChar((y[0].unicode() - z + y[2].unicode() - z) % 2 + z);
			QChar x3 = QChar((y[0].unicode() - z + y[1].unicode() - z + y[2].unicode() - z) % 2 + z);
			y1.append(x1);
			y1.append(x2);
			y1.append(x3);
			int dis0 = Hammingdistance(y1, x);
			int first1 = w2[0] + dis0;
			y = s2[0] + '0';
			w1.push_back(first1);     //01状态输入0转为00状态
			s1.push_back(y);
			QString k, k1;
			k.push_back("1");   //输入为1
			k.push_back(s2[0].back());
			k.push_back(s2[0][p - 2]);
			QChar x4 = k[0];
			QChar x5 = QChar((k[0].unicode() - z + k[2].unicode() - z) % 2 + z);
			QChar x6 = QChar((k[0].unicode() - z + k[1].unicode() - z + k[2].unicode() - z) % 2 + z);
			k1.append(x4);
			k1.append(x5);
			k1.append(x6);
			int dis1 = Hammingdistance(k1, x);
			int first2 = w2[0] + dis1;
			k = s2[0] + '1';
			w3.push_back(first2);   //01状态输入1跳转到10状态
			s3.push_back(k);
			auto it = w2.begin();
			auto it1 = s2.begin();
			w2.erase(it);           //将原来的值清除，保证其中的元素不超过3个
			s2.erase(it1);
		}

		if (w3.size() != 0)    //计算状态3
		{
			int p = s3[0].size();
			QString y, y1;
			y.push_back("0");   //输入为0
			y.push_back(s3[0].back());
			y.push_back(s3[0][p - 2]);
			QChar x1 = y[0];
			QChar x2 = QChar((y[0].unicode() - z + y[2].unicode() - z) % 2 + z);
			QChar x3 = QChar((y[0].unicode() - z + y[1].unicode() - z + y[2].unicode() - z) % 2 + z);
			y1.append(x1);
			y1.append(x2);
			y1.append(x3);
			int dis0 = Hammingdistance(y1, x);
			int first1 = w3[0] + dis0;
			y = s3[0] + '0';
			w2.push_back(first1);     //10状态输入0转为01状态
			s2.push_back(y);
			QString k, k1;
			k.push_back("1");   //输入为1
			k.push_back(s3[0].back());
			k.push_back(s3[0][p - 2]);
			QChar x4 = k[0];
			QChar x5 = QChar((k[0].unicode() - z + k[2].unicode() - z) % 2 + z);
			QChar x6 = QChar((k[0].unicode() - z + k[1].unicode() - z + k[2].unicode() - z) % 2 + z);
			k1.append(x4);
			k1.append(x5);
			k1.append(x6);
			int dis1 = Hammingdistance(k1, x);
			int first2 = w3[0] + dis1;
			k = s3[0] + '1';
			w4.push_back(first2);   //10状态输入1跳转到11状态
			s4.push_back(k);
			auto it = w3.begin();
			auto it1 = s3.begin();
			w3.erase(it);           //将原来的值清除，保证其中的元素不超过3个
			s3.erase(it1);
		}

		if (w4.size() != 0 && i != 1)    //计算状态4
		{
			int p = s4[0].size();
			QString y, y1;
			y.push_back("0");   //输入为0
			y.push_back(s4[0].back());
			y.push_back(s4[0][p - 2]);
			QChar x1 = y[0];
			QChar x2 = QChar((y[0].unicode() - z + y[2].unicode() - z) % 2 + z);
			QChar x3 = QChar((y[0].unicode() - z + y[1].unicode() - z + y[2].unicode() - z) % 2 + z);
			y1.append(x1);
			y1.append(x2);
			y1.append(x3);
			int dis0 = Hammingdistance(y1, x);
			int first1 = w4[0] + dis0;
			y = s4[0] + '0';
			w2.push_back(first1);     //11状态输入0转为01状态
			s2.push_back(y);
			QString k, k1;
			k.push_back("1");   //输入为1
			k.push_back(s4[0].back());
			k.push_back(s4[0][p - 2]);
			QChar x4 = k[0];
			QChar x5 = QChar((k[0].unicode() - z + k[2].unicode() - z) % 2 + z);
			QChar x6 = QChar((k[0].unicode() - z + k[1].unicode() - z + k[2].unicode() - z) % 2 + z);
			k1.append(x4);
			k1.append(x5);
			k1.append(x6);
			int dis1 = Hammingdistance(k1, x);
			int first2 = w4[0] + dis1;
			k = s4[0] + '1';
			w4.push_back(first2);   //11状态输入1还是11状态
			s4.push_back(k);
			auto it = w4.begin();
			auto it1 = s4.begin();
			w4.erase(it);           //将原来的值清除，保证向量中的元素不超过3个
			s4.erase(it1);
		}

		if (w1.size() >= 2)        //淘汰误比特数较大的分支
		{
			if (w1[0] > w1[1])
			{
				auto it = w1.begin();
				auto it1 = s1.begin();
				w1.erase(it);
				s1.erase(it1);
			}
			else
			{
				auto it = w1.begin() + 1;
				auto it1 = s1.begin() + 1;
				w1.erase(it);
				s1.erase(it1);
			}
		}

		if (w2.size() >= 2)
		{
			if (w2[0] > w2[1])
			{
				auto it = w2.begin();
				auto it1 = s2.begin();
				w2.erase(it);
				s2.erase(it1);
			}
			else
			{
				auto it = w2.begin() + 1;
				auto it1 = s2.begin() + 1;
				w2.erase(it);
				s2.erase(it1);
			}
		}

		if (w3.size() >= 2)
		{
			if (w3[0] > w3[1])
			{
				auto it = w3.begin();
				auto it1 = s3.begin();
				w3.erase(it);
				s3.erase(it1);
			}
			else
			{
				auto it = w3.begin() + 1;
				auto it1 = s3.begin() + 1;
				w3.erase(it);
				s3.erase(it1);
			}
		}

		if (w4.size() >= 2)
		{
			if (w4[0] > w4[1])
			{
				auto it = w4.begin();
				auto it1 = s4.begin();
				w4.erase(it);
				s4.erase(it1);
			}
			else
			{
				auto it = w4.begin() + 1;
				auto it1 = s4.begin() + 1;
				w4.erase(it);
				s4.erase(it1);
			}
		}
	}
	int max = INT_LEAST8_MAX;    //找到误比特数最小的分支
	if (max > w1[0])
	{
		max = w1[0];
		a = s1[0];
	}
	if (max > w2[0])
	{
		max = w2[0];
		a = s2[0];
	}
	if (max > w3[0])
	{
		max = w3[0];
		a = s3[0];
	}
	if (max > w4[0])
	{
		max = w4[0];
		a = s4[0];
	}
	if (a.size() == k)    
		return a;
	else
	{
		a.remove(0, 2);    //将设置初始状态的0清除
		return a;
	}
}

QString ConvolutionalcodeClass::yDecode(QString b)    //硬判决译码
{
	QString a;
	int n = b.size();
	if (n % 3 != 0)
		return a;
	int k = n / 3;
	QChar zero = '0';
	char16_t z = zero.unicode();  

	for (int i = 0; i < k; i++)
	{
		QString x;
		for (int j = 0; j <= 2; j++)
		{
			if (b[i * 3 + j].unicode() != z && b[i * 3 + j].unicode() != z + 1) //二进制序列只允许0和1存在
			{
				QString g;
				return g;
			}
			x.append(b[i * 3 + j]);
		}
		if (x == "111")   //根据三元组的类型直接判断原码
			a.append('1');
		if (x == QString("000"))
			a.append('0');
		if (x == QString("011"))
			a.append('0');
		if (x == QString("100"))
			a.append('1');
		if (x == QString("001"))
			a.append('0');
		if (x == QString("110"))
			a.append('1');
		if (x == QString("101"))
			a.append('1');
		if (x == QString("010"))
			a.append('0');
	}
	return a;
}

int Hammingdistance(QString a, QString b)   //计算两字符串的汉明距离
{
	int sum = 0;
	int m = a.size();
	int n = b.size();
	if (m != n)
		return 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] != b[i])
			sum++;
	}
	return sum;
}