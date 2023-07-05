#include<stack>
#include "Calculator_Qt.h"
#include <iostream>

Calculator_Qt::Calculator_Qt(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    on_AC_btn_clicked();
}

Calculator_Qt::~Calculator_Qt()
{
}

void Calculator_Qt::on_btn0_clicked()
{
    ui.label1->setText(ui.label1->text() + "0");
}

void Calculator_Qt::on_btn1_clicked()
{
    ui.label1->setText(ui.label1->text() + "1");
}

void Calculator_Qt::on_btn2_clicked()
{
    ui.label1->setText(ui.label1->text() + "2");
}

void Calculator_Qt::on_btn3_clicked()
{
    ui.label1->setText(ui.label1->text() + "3");
}

void Calculator_Qt::on_btn4_clicked()
{
    ui.label1->setText(ui.label1->text() + "4");
}

void Calculator_Qt::on_btn5_clicked()
{
    ui.label1->setText(ui.label1->text() + "5");
}

void Calculator_Qt::on_btn6_clicked()
{
    ui.label1->setText(ui.label1->text() + "6");
}

void Calculator_Qt::on_btn7_clicked()
{
    ui.label1->setText(ui.label1->text() + "7");
}

void Calculator_Qt::on_btn8_clicked()
{
    ui.label1->setText(ui.label1->text() + "8");
}

void Calculator_Qt::on_btn9_clicked()
{
    ui.label1->setText(ui.label1->text() + "9");
}

void Calculator_Qt::on_dot_btn_clicked()
{
    ui.label1->setText(ui.label1->text() + ".");
}

void Calculator_Qt::on_ans_btn_clicked()
{
    
}

void Calculator_Qt::on_equal_btn_clicked()
{
	std::cout << "in solve\n";
	this->Solve();
	std::cout << "from solve\n";
}

void Calculator_Qt::on_plus_btn_clicked()
{
    ui.label1->setText(ui.label1->text() + "+");
}

void Calculator_Qt::on_minus_btn_clicked()
{
    ui.label1->setText(ui.label1->text() + "-");
}

void Calculator_Qt::on_mult_btn_clicked()
{
    ui.label1->setText(ui.label1->text() + "*");
}

void Calculator_Qt::on_divide_btn_clicked()
{
    ui.label1->setText(ui.label1->text() + "/");
}

void Calculator_Qt::on_rightBracket_btn_clicked()
{
    ui.label1->setText(ui.label1->text() + ")");
}

void Calculator_Qt::on_leftBracket_btn_clicked()
{
    ui.label1->setText(ui.label1->text() + "(");
}

void Calculator_Qt::on_modulas_btn_clicked()
{
    ui.label1->setText(ui.label1->text() + "%");
}

void Calculator_Qt::on_power_btn_clicked()
{
    ui.label1->setText(ui.label1->text() + "^");
}

void Calculator_Qt::on_AC_btn_clicked()
{
    ui.label1->clear();
}

void Calculator_Qt::on_Del_btn_clicked()
{
    ui.label1->setText(ui.label1->text().left(ui.label1->text().length() - 1));
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
	char t = 'y', op;
	std::string line, num, s;
	double num1, num2;
	bool brackets, percentage;
	std::stack<std::string>temp;

	//cout << "Hello to calculator\n";
	while (t == 'y')
	{
		//cout << "\n--> ";
		//cin >> line;
		line = ui.label1->text().toStdString();

		std::string Postfix;
		num = "";
		percentage = brackets = false;
		for (int i = 0; i < line.size(); ++i)
		{
			if (('0' <= line[i] && line[i] <= '9') || line[i] == '.') { //a number
				num += line[i];
				percentage = false;
			}
			else {
				if (num != "") {
					Postfix += num + " ";
					num = "";
				}

				if (percentage) {
					temp.pop();
					Postfix += "p";
					percentage = false;
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

		Postfix += num;

		while (!temp.empty())
		{
			Postfix += temp.top();
			temp.pop();
		}

		//cout << "The Postfix: " << Postfix << endl;

		std::stack<double> numbers;
		double num1, num2, dot = 10;

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
		ui.label2->setText(QString::number(numbers.top()));

		//cout << "\nIf you want to try again enter (y) \n";
		//cin >> t;
		t = 'n';
	}

	return 0;

}