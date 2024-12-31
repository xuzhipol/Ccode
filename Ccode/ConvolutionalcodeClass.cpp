#include "ConvolutionalcodeClass.h"

QString ConvolutionalcodeClass::Encode(QString b)   //�����ؼ������еĵ�һ�����������
{
	QString d = "00" + b;   //���ñ�������ʼ״̬Ϊȫ��
	QString c;
	int n = d.size();
	if (n == 2)     //����Ϊ�գ���ֱ�ӷ��ؿմ�
		return c;
	QChar zero = '0';
	//char16_t�̶�Ϊ16λ�����������洢UTF-16�����16λunicode�ַ�
	char16_t z = zero.unicode();   //����õ�'0'��unicodeֵ�������������
	for (int i = 2; i < n; i++)
	{
		if (d[i].unicode() != z && d[i].unicode() != z + 1) //����������ֻ����0��1����
		{
			QString g;
			return g;
		}
		QChar x1 = d[i];
		//��'0'��unicodeֵ��������ɵõ�intֵ0��1��֮���ٽ���ģ�������㣬�õ�����ֵ
		QChar x2 = QChar((d[i].unicode() - z + d[i - 2].unicode() - z) % 2 + z);
		//����QChar()��һ���캯����unicodeֵת��ΪQChar���ͣ��Է��㹹��QString�ַ���
		QChar x3 = QChar((d[i].unicode() - z + d[i - 2].unicode() - z + d[i-1].unicode() - z) % 2 + z);
		c.append(x1);  //��ĩβ����ַ����Ӷ�����������ַ���
		c.append(x2);
		c.append(x3);
	}
	return c;
}

int Hammingdistance(QString a, QString b);   //��������


QString ConvolutionalcodeClass::rDecode(QString b)     //ά�ر����룬��һ�ֿ�����������ǿ�����뷽��
{
	QString a;
	int n = b.size();
	if (n % 3 != 0)
		return a;
	int k = n / 3;
	QChar zero = '0';
	char16_t z = zero.unicode();

	//״̬1������(00)
	std::vector<int> w1;       //�洢�ۼӵ��������
	std::vector<QString> s1;   //�洢ÿһ���õ����Ӵ�
	w1.push_back(0);
	s1.push_back("00");

	//״̬2������(01)
	std::vector<int> w2;
	std::vector<QString> s2;

	//״̬3������(10)
	std::vector<int> w3;
	std::vector<QString> s3;

	//״̬4������(11)
	std::vector<int> w4;
	std::vector<QString> s4;

	for (int i = 0; i < k; i++)
	{
		QString x;
		for (int j = 0; j <= 2; j++)
		{
			if (b[i * 3 + j].unicode() != z && b[i * 3 + j].unicode() != z + 1) //����������ֻ����0��1����
			{
				QString g;
				return g;
			}
			x.append(b[i * 3 + j]);
		}
		if (k == 1)           //���У����ֻ��3���أ�����Ӳ�о����һ��
		{
			if (x == "111")   //������Ԫ�������ֱ���ж�ԭ��
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
		if (w1.size() != 0)        //����״̬1
		{
			int p = s1[0].size();
			QString y, y1;
			y.push_back("0");   //����Ϊ0
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
			w1.push_back(first1);     //00״̬����0��Ȼ��00״̬
			s1.push_back(y);
			QString k, k1;
			k.push_back("1");   //����Ϊ1
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
			w3.push_back(first2);   //00״̬����1��ת��10״̬
			s3.push_back(k);
			auto it = w1.begin();
			auto it1 = s1.begin();
			w1.erase(it);           //��ԭ����ֵ�������֤���е�Ԫ�ز�����3��
			s1.erase(it1);
		}

		if (i == 0)
			continue;

		if (w2.size() != 0 && i != 1)    //����״̬2
		{
			int p = s2[0].size();
			QString y, y1;
			y.push_back("0");   //����Ϊ0
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
			w1.push_back(first1);     //01״̬����0תΪ00״̬
			s1.push_back(y);
			QString k, k1;
			k.push_back("1");   //����Ϊ1
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
			w3.push_back(first2);   //01״̬����1��ת��10״̬
			s3.push_back(k);
			auto it = w2.begin();
			auto it1 = s2.begin();
			w2.erase(it);           //��ԭ����ֵ�������֤���е�Ԫ�ز�����3��
			s2.erase(it1);
		}

		if (w3.size() != 0)    //����״̬3
		{
			int p = s3[0].size();
			QString y, y1;
			y.push_back("0");   //����Ϊ0
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
			w2.push_back(first1);     //10״̬����0תΪ01״̬
			s2.push_back(y);
			QString k, k1;
			k.push_back("1");   //����Ϊ1
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
			w4.push_back(first2);   //10״̬����1��ת��11״̬
			s4.push_back(k);
			auto it = w3.begin();
			auto it1 = s3.begin();
			w3.erase(it);           //��ԭ����ֵ�������֤���е�Ԫ�ز�����3��
			s3.erase(it1);
		}

		if (w4.size() != 0 && i != 1)    //����״̬4
		{
			int p = s4[0].size();
			QString y, y1;
			y.push_back("0");   //����Ϊ0
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
			w2.push_back(first1);     //11״̬����0תΪ01״̬
			s2.push_back(y);
			QString k, k1;
			k.push_back("1");   //����Ϊ1
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
			w4.push_back(first2);   //11״̬����1����11״̬
			s4.push_back(k);
			auto it = w4.begin();
			auto it1 = s4.begin();
			w4.erase(it);           //��ԭ����ֵ�������֤�����е�Ԫ�ز�����3��
			s4.erase(it1);
		}

		if (w1.size() >= 2)        //��̭��������ϴ�ķ�֧
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
	int max = INT_LEAST8_MAX;    //�ҵ����������С�ķ�֧
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
		a.remove(0, 2);    //�����ó�ʼ״̬��0���
		return a;
	}
}

QString ConvolutionalcodeClass::yDecode(QString b)    //Ӳ�о�����
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
			if (b[i * 3 + j].unicode() != z && b[i * 3 + j].unicode() != z + 1) //����������ֻ����0��1����
			{
				QString g;
				return g;
			}
			x.append(b[i * 3 + j]);
		}
		if (x == "111")   //������Ԫ�������ֱ���ж�ԭ��
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

int Hammingdistance(QString a, QString b)   //�������ַ����ĺ�������
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