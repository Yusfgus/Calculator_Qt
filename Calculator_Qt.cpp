#include<stack>
#include "Calculator_Qt.h"
#include <iostream>
#include <QIntValidator>

Calculator_Qt::Calculator_Qt(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	ui.screen1->clear();
	ui.screen2->clear();
	ui.ans_btn->setEnabled(false);
	ans = 0;
	newline = false;
}

Calculator_Qt::~Calculator_Qt()
{
}

void Calculator_Qt::on_btn0_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "0");
}

void Calculator_Qt::on_btn1_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "1");
}

void Calculator_Qt::on_btn2_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "2");
}

void Calculator_Qt::on_btn3_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "3");
}

void Calculator_Qt::on_btn4_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "4");
}

void Calculator_Qt::on_btn5_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "5");
}

void Calculator_Qt::on_btn6_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "6");
}

void Calculator_Qt::on_btn7_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "7");
}

void Calculator_Qt::on_btn8_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "8");
}

void Calculator_Qt::on_btn9_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "9");
}

void Calculator_Qt::on_dot_btn_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + ".");
}

void Calculator_Qt::on_ans_btn_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "ans");
}

void Calculator_Qt::on_equal_btn_clicked()
{
	if (ui.screen1->text() != "") {
		this->Solve();
		ui.ans_btn->setEnabled(true);
		ui.screen1->setAlignment(Qt::AlignRight);
		ui.screen1->setEnabled(false);
		newline = true;
	}
}

void Calculator_Qt::newLine()
{
	if (!newline) return;
	newline = false;
	ui.screen2->setText(ui.screen2->text() + " = " + ui.screen1->text());
	ui.screen1->clear();
	ui.screen1->setAlignment(Qt::AlignLeft);
	ui.screen1->setEnabled(true);
	ui.screen1->setText(QString::number(ans));
}

void Calculator_Qt::on_plus_btn_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "+");
}

void Calculator_Qt::on_minus_btn_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "-");
}

void Calculator_Qt::on_mult_btn_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "*");
}

void Calculator_Qt::on_divide_btn_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "/");
}

void Calculator_Qt::on_rightBracket_btn_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + ")");
}

void Calculator_Qt::on_leftBracket_btn_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "(");
}

void Calculator_Qt::on_modulas_btn_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "%");
}

void Calculator_Qt::on_power_btn_clicked()
{
	newLine();
	ui.screen1->setText(ui.screen1->text() + "^");
}

void Calculator_Qt::on_AC_btn_clicked()
{
	newLine();
	ui.screen1->clear();
}

void Calculator_Qt::on_Del_btn_clicked()
{
	newLine();
	int i = 1;
	if (ui.screen1->text().length() >= 3 && ui.screen1->text()[ui.screen1->text().length() - 3] == 'a')
		i = 3;

	ui.screen1->setText(ui.screen1->text().left(ui.screen1->text().length() - i));
}

double Add(double num1, double num2)
{
	return num1 + num2;
}

double Sub(double num1, double num2)
{
	return num1 - num2;
}

double mult(double num1, double num2)
{
	return num1 * num2;
}

double dive(double num1, double num2)
{
	return num1 / num2;
}

int mod(double num1, double num2)
{
	int a = num1, b = num2;
	if (num1 != a || num2 != b) {
		//cout << "Syntax Error\n";
		exit(0);
	}
	return a % b;
}

int Calculator_Qt::Solve()
{
	char op;
	std::string line, num, s, Postfix;
	double num1, num2, dot = 10;
	bool brackets, percentage, negative=false;
	std::stack<std::string>temp;
	std::stack<double> numbers;

	line = ui.screen1->text().toStdString();

	num = "";
	percentage = brackets = false;
	for (int i = 0; i < line.size(); ++i)
	{
		if (('0' <= line[i] && line[i] <= '9') || line[i] == '.') { //a number
			num += line[i];
			percentage = false;
		}
		else if (line[i] == 'a') {
			num += std::to_string(ans);
			i += 2;
		}
		else {
			if (num != "") {
				if (negative)
				{
					Postfix += num + "-";
					num = "";
					negative = false;
				}
				Postfix += num + " ";
				num = "";
			}

			if (percentage) {
				temp.pop();
				Postfix += "p";
				percentage = false;
			}

			if (line[i] == '-' && i == 0)
			{
				Postfix += "0 ";
				negative = true;
				continue;
			}
			if (line[i] == '-' && i > 0)
			{
				if (line[i - 1] < '0' || line[i - 1] > '9' || i == 0)
				{
					Postfix += "0 ";
					negative = true;
					continue;
				}

			}

			if (!temp.empty() && !brackets && line[i] != '(' && line[i] != '^' && line[i] != '%')
			{
				if (temp.top() == "*" || temp.top() == "/" || temp.top() == "^" || temp.top() == "%") {
					Postfix += temp.top();
					temp.pop();
				}
			}

			if (line[i] == '(') {
				temp.push("(");
				brackets = true;
			}
			else if (line[i] == ')')
			{
				while (!temp.empty() && temp.top() != "(")
				{
					Postfix += temp.top();
					temp.pop();
				}
				temp.pop();
				brackets = false;
			}
			else {
				
				s = line[i];
				temp.push(s);
				if (line[i] == '%')
					percentage = true;
			}
		}
	}

	if (percentage) {
		temp.pop();
		Postfix += "p";
	}

	if (negative)
	{
		Postfix += num + "-";
		num = "";
		negative = false;
	}
	else
	{
		Postfix += num;
	}

	while (!temp.empty())
	{
		Postfix += temp.top();
		temp.pop();
	}

	std::cout << "The Postfix: " << Postfix << std::endl;


	for (size_t i = 0; i < Postfix.size(); i++)
	{

		if ((Postfix[i] >= '0' && Postfix[i] <= '9') || Postfix[i] == '.')
		{

			num1 = Postfix[i] - 48;
			while (Postfix[i + 1] >= '0' && Postfix[i + 1] <= '9')
			{
				num1 *= 10;
				num1 += (Postfix[i + 1] - 48);
				i++;
			}

			if (Postfix[i + 1] == '.')
			{
				i += 2;
				num1 += (Postfix[i] - 48) / dot;
				while (Postfix[i + 1] >= '0' && Postfix[i + 1] <= '9')
				{
					dot /= 10;
					num1 += ((Postfix[i + 1] - 48)) / dot;
					i++;
				}

			}

			dot = 10;
			numbers.push(num1);
		}
		else if (Postfix[i] == ' ')
			continue;
		else if (Postfix[i] == 'p')
		{
			num1 = numbers.top();
			numbers.pop();
			num1 = num1 / 100;
			numbers.push(num1);
		}
		else {
			num2 = numbers.top();
			numbers.pop();
			num1 = numbers.top();
			numbers.pop();

			if (Postfix[i] == '-')
				numbers.push(Sub(num1, num2));
			else if (Postfix[i] == '+')
				numbers.push(Add(num1, num2));
			else if (Postfix[i] == '*')
				numbers.push(mult(num1, num2));
			else if (Postfix[i] == '/')
				numbers.push(dive(num1, num2));
			else if (Postfix[i] == '%')
				numbers.push(mod(num1, num2));
			else if (Postfix[i] == '^')
				numbers.push(pow(num1, num2));
		}
	}

	//cout << "The answer: " << numbers.top() << endl;
	ui.screen2->setText(ui.screen1->text());
	ui.screen1->setText(QString::number(numbers.top()));

	ans = numbers.top();

	return 0;
}

void Calculator_Qt::on_change_theme_btn_clicked()
{
	QString style1, style2, style3, style4;
	if (ui.change_theme_btn->text() == "dark") // currently it's light mode
	{
		ui.change_theme_btn->setStyleSheet("border-radius: 10px;background: #2E3138; color: #1E86CF;");
		ui.change_theme_btn->setText("light");
		ui.centralWidget->setStyleSheet("background-color: #0B0C0D ;");
		ui.screen1->setStyleSheet("border: none; color: #E1E1E1; font-family: Inter; font-size: 40px; font-style: normal; font-weight: 500; line-height: normal; ");
		ui.equal_btn->setStyleSheet("color: #B2DAFF; font-family: Inter;font-size: 30px; font-style: normal; font-weight: 500 ; border-radius: 14px; background: #1991FF; ");
		style1 = "border-radius: 14px;background: #2E3138; color: #1E86CF; font-family: Inter; font-size: 30px; font-style: normal ; font-weight:500;";
		style2 = "border-radius: 14px; background: #005DB2; color: #84C3FD;font-family: Inter;font-size: 30px;font-style: normal;font-weight: 500;line-height: normal; ";
		style3 = "border-radius: 10px; background: #005DB2; color: #84C3FD;font-family: Inter;font-size: 15px;font-style: normal;font-weight: 500;line-height: normal; ";
		style4 = "border-radius: 14px; background: #616161; color: #A0A1A2; font-family: Inter; font-size: 28px; ";
	}
	else // currently it's dark mode
	{
		ui.change_theme_btn->setStyleSheet("border-radius: 10px;\nbackground: #B2E3FF;\nfont-family: Inter;\n\n\n");
		ui.change_theme_btn->setText("dark");
		ui.centralWidget->setStyleSheet("");
		ui.screen1->setStyleSheet("border : none;\nbackground: transparent;\n\ncolor: #000;\nfont-family: Inter;\nfont-size: 35px;\nfont-style: normal;\nfont-weight: 500;\nline-height: normal;");
		ui.equal_btn->setStyleSheet("border-radius: 14px;\nbackground: #19ACFF;\n\ncolor: #CEE4F8;\nfont-family: Inter;\nfont-size: 30px;\nfont-style: normal;\nfont-weight: 500;\nline-height: normal;");
		style1 = style4 = "border-radius: 14px;\nbox-shadow: 10px 10px 10px 0px rgba(255, 255, 255, 0.25) inset;\ncolor: #1E86CF;\nfont-family: Inter;\nfont-size: 30px;\nfont-style: normal;\nfont-weight: 500;\nline-height: normal;\n\n";
		style2 = "border-radius: 14px;\nbackground: #ADE1FF;\ncolor: #1E86CF;\nfont-family: Inter;\nfont-size: 30px;\nfont-style: normal;\nfont-weight: 500;\nline-height: normal;";
		style3 = "border-radius: 10px;\nbackground: #ADE1FF;\n\ncolor: #1E86CF;\nfont-family: Inter;\nfont-size: 15px;\nfont-style: normal;\nfont-weight: 500;\nline-height: normal;";
	}

	ui.btn0->setStyleSheet(style1);
	ui.btn1->setStyleSheet(style1);
	ui.btn2->setStyleSheet(style1);
	ui.btn3->setStyleSheet(style1);
	ui.btn4->setStyleSheet(style1);
	ui.btn5->setStyleSheet(style1);
	ui.btn6->setStyleSheet(style1);
	ui.btn7->setStyleSheet(style1);
	ui.btn8->setStyleSheet(style1);
	ui.btn9->setStyleSheet(style1);
	ui.ans_btn->setStyleSheet(style1);
	ui.dot_btn->setStyleSheet(style1);

	ui.plus_btn->setStyleSheet(style2);
	ui.minus_btn->setStyleSheet(style2);
	ui.mult_btn->setStyleSheet(style2);
	ui.divide_btn->setStyleSheet(style2);

	ui.rightBracket_btn->setStyleSheet(style3);
	ui.leftBracket_btn->setStyleSheet(style3);
	ui.modulas_btn->setStyleSheet(style3);
	ui.power_btn->setStyleSheet(style3);

	ui.AC_btn->setStyleSheet(style4);
	ui.Del_btn->setStyleSheet(style4);
}

void Calculator_Qt::on_screen1_textChanged()
{
	if (ui.screen1->text() == "")return;
	int length = ui.screen1->text().length();
	QChar newChar = ui.screen1->text()[length - 1];
	QString valid = "0123456789.+-*/^%()";
	if (valid.contains(newChar) || length >= 3 && ui.screen1->text()[length - 3] == 'a')
		return;
	else
		this->on_Del_btn_clicked();
}