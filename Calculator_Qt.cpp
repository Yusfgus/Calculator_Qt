#include <stack>
#include "Calculator_Qt.h"
#include <iostream>
#include <QIntValidator>
#define cout std::cout
#define endl '\n'

Calculator_Qt::Calculator_Qt(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	ui.screen1->clear();
	ui.screen2->clear();
	ui.textBrowser->clear();
	ui.ans_btn->setEnabled(false);
	ans = 0;
	newline = false;
	Animation_1 = new QPropertyAnimation(ui.image_button, "geometry");
	Animation_2 = new QPropertyAnimation(ui.image_button, "geometry");
	Animation_3 = new QPropertyAnimation(this, "geometry");
	Animation_4 = new QPropertyAnimation(this, "geometry");
	history = "";
	show_history = false;
	//testCases();
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
		if (this->Solve() == -1) return;
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
	ui.screen1->setText("ans");
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
	ui.screen1->setEnabled(true);
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

int mod(double num1, double num2, bool& flag)
{
	int a = num1, b = num2;
	if (num1 != a || num2 != b) {
		//cout << "Syntax Error\n";
		flag = true;
		return 0;
		//exit(0);
	}
	return a % b;
}

bool isOper(const char& c)
{
	return (c == '^' || c == '%' || c == '/' || c == '*');
}

bool isOper(const std::string& c)
{
	return (c == "^" || c == "%" || c == "/" || c == "*");
}

bool isSign(const char& c)
{
	return (c == '+' || c == '-' || c == 'n');
}

void improve(std::string& line)
{
	int sz = line.size();
	bool digit = false;
	for (int i = 0; i < sz - 1; ++i)
	{
		if (isdigit(line[i]) || line[i] == 'a')digit = true;
		else if (line[i] == '(') digit = false;

		if (line[i] == '+' && (isSign(line[i + 1]) || i == 0 || isOper(line[i - 1]) || line[i - 1] == ' ' && !digit))
			line[i] = ' ';
		else if (line[i] == '-')
		{
			if (line[i + 1] == '-')
				line[i] = ' ', line[i + 1] = '+';
			else if (line[i + 1] == '+')
				line[i] = ' ', line[i + 1] = '-';
			else if (line[i + 1] == '(' && (i == 0 || !isdigit(line[i - 1])))
				line[i] = 'n';
			else if (i == 0 || !digit && line[i - 1] == ' ' || !isdigit(line[i - 1]) && line[i - 1] != ')' && line[i - 1] != ' ' && line[i - 1] != 's')
				line[i] = 'n';
		}
		else if (i > 0 && line[i] == '(' && (isdigit(line[i - 1]) || line[i - 1] == 's'))
			line = line.substr(0, i - 1) + '*' + line.substr(i++, sz++);
		else if (line[i] == '.' && (i == 0 || !isdigit(line[i - 1]) && line[i - 1] != 's'))
			line = line.substr(0, i - 1) + '0' + line.substr(i++, sz++);

	}
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
}

bool syntaxError(const std::string& line)
{
	int sz = line.size(), br = 0;
	if (!isdigit(line[0]) && !isSign(line[0]) && line[0] != '(' && line[0] != 'a' && line[0] != 'n') //first index
		return true;

	if (!isdigit(line[sz - 1]) && line[sz - 1] != '%' && line[sz - 1] != ')' && line[sz - 1] != 's') //last index
		return true;

	if (line[0] == '(')
		++br;

	for (int i = 1; i < sz; ++i)
	{
		if (isOper(line[i]) && (isOper(line[i - 1]) || isSign(line[i - 1])))
			return true;
		if (line[i] == '(') {
			++br;
		}
		else if (line[i] == ')') {
			if (--br < 0)
				return true;
		}
		else if (line[i] == '.' && !isdigit(line[i - 1]))
			return true;
		else if (line[i] == 's' && i + 1 < sz && isdigit(line[i + 1]))
			return true;
	}
	if (br > 0)
		return true;

	return false;
}

bool mathError(const std::string& line)
{
	int sz = line.size();
	for (int i= 0; i<sz; ++i)
	{
		if (line[i] == '/' && line[i + 1] == '0')
			return true;
	}

	return false;
}

double Calculator_Qt::Solve()
{
	char op;
	std::string line, num, s, Postfix;
	double num1, num2, dot = 10;
	bool brackets, percentage, negative, negBracket;
	std::stack<std::string>temp;
	std::stack<double> numbers;

	line = ui.screen1->text().toStdString();
	improve(line);
	if (syntaxError(line)) {
		ui.screen1->setAlignment(Qt::AlignLeft);
		ui.screen1->setText("Syntax Error");
		ui.screen1->setEnabled(false);
		return -1;
	}
	if (mathError(line)) {
		ui.screen1->setAlignment(Qt::AlignLeft);
		ui.screen1->setText("Math Error");
		ui.screen1->setEnabled(false);
		return -1;
	}
	cout << "The line:" << line << endl;

	num = "";
	negBracket = negative = percentage = brackets = false;
	//cout << "line: " << line << "\nStack: ";
	for (int i = 0; i < line.size(); ++i)
	{
		if (isdigit(line[i]) || line[i] == '.') { //a number
			num += line[i];
			percentage = false;
		}
		else if (line[i] == 'a') {
			if (ans < 0) {
				negative = !negative;
				ans *= -1;
			}
			num += std::to_string(ans);
			if (negative) {
				Postfix += 'n';
				negative = false;
			}
			i += 2;
		}
		else if (line[i] == 'n') {
			if (line[i + 1] == '(')
			{
				Postfix += "0 ";
				temp.push("-");
			}
			else
				negative = true;
		}
		else {
			if (num != "") {
				if (negative) {
					Postfix += 'n';
					negative = false;
				}
				Postfix += num + " ";
				num = "";
			}

			if (line[i] == '(') percentage = false;

			if (percentage) {
				temp.pop();
				Postfix += "p ";
				percentage = false;
			}

			if (!temp.empty() && line[i] != '(' && line[i] != '^' && line[i] != '%')
			{
				if (isOper(temp.top()))
				{
					Postfix += temp.top() + " ";
					temp.pop();
				}

				if (!temp.empty() && temp.top() != "(" && (isSign(line[i]))) {
					Postfix += temp.top() + " ";
					temp.pop();
				}
			}

			if (line[i] == ')')
			{
				while (!temp.empty() && temp.top() != "(")
				{
					Postfix += temp.top() + " ";
					temp.pop();
				}
				temp.pop();
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
		Postfix += "p ";
	}

	if (negative) {
		num = 'n' + num;
		negative = false;
		//temp.pop();
	}

	Postfix += num + " ";

	while (!temp.empty())
	{
		Postfix += temp.top() + ' ';
		temp.pop();
	}

	cout << "Postfix: " << Postfix << "\n\n";

	for (size_t i = 0; i < Postfix.size(); i++)
	{
		if (isdigit(Postfix[i]) || Postfix[i] == '.')
		{
			num1 = Postfix[i] - 48;
			while (isdigit(Postfix[i + 1]))
			{
				num1 *= 10;
				num1 += (Postfix[i + 1] - 48);
				i++;
			}
			if (Postfix[i + 1] == '.')
			{
				i += 2;
				num1 += (Postfix[i] - 48) / dot;
				while (isdigit(Postfix[i + 1]))
				{
					dot /= 10;
					num1 += ((Postfix[i + 1] - 48)) / dot;
					i++;
				}
			}
			dot = 10;
			if (negative) {
				num1 *= -1;
				negative = false;
			}
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
		else if (Postfix[i] == 'n')
		{
			negative = true;
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
			else if (Postfix[i] == '%') {
				bool flag = false;
				int a = mod(num1, num2, flag);
				if (flag) {
					ui.screen1->setAlignment(Qt::AlignLeft);
					ui.screen1->setText("Syntax Error");
					ui.screen1->setEnabled(false);
					return -1;
				}
				else
					numbers.push(a);
			}
			else if (Postfix[i] == '^')
				numbers.push(pow(num1, num2));
		}
	}

	//cout << "The answer: " << numbers.top() << endl;

	if (ui.screen2->text() != "")
	{
		if (history != "")
			history += "\n"+ ui.screen2->text();
		else
			history = ui.screen2->text();
		ui.textBrowser->setText(history);
	}
	ui.screen2->setText(ui.screen1->text());
	ui.screen1->setText(QString::number(numbers.top()));




	ans = numbers.top();

	return 0;
}


void Calculator_Qt::on_image_button_clicked()
{
	QString style1, style2, style3, style4;
	if (ui.change_theme_btn->text() == "dark") // currently it's light mode
	{
		ui.change_theme_btn->setStyleSheet("border-radius: 13px;background: #2E3138; color:#2E3138;");
		ui.change_theme_btn->setText("light");
		//Animation//
		ui.image_button->setStyleSheet(" background-image:url(:/Calculator_Qt/Screenshot 2023-07-08 021102.png); background-repeat: no-repeat; border-radius: 10px; font-family: Inter; ");
		Animation_1 = new QPropertyAnimation(ui.image_button, "geometry");
		Animation_1->setDuration(270);
		Animation_1->setStartValue(ui.image_button->geometry());
		Animation_1->setEndValue(QRect(32, 10, 24, 22));
		Animation_1->start();
		////////////////////////////
		ui.centralWidget->setStyleSheet("background-color: #0B0C0D ;");
		ui.screen1->setStyleSheet("border: none; color: #E1E1E1; font-family: Inter; font-size: 35px; font-style: normal; font-weight: 500; line-height: normal; ");
		ui.textBrowser->setStyleSheet("border: none; color: #5C5B5B; font-family: Inter; font-size: 15px; font-style: normal; ");
		ui.history_btn->setStyleSheet("border-radius: 13px; background-image: url(:/Calculator_Qt/history icon 4.png);");
		ui.equal_btn->setStyleSheet("color: #B2DAFF; font-family: Inter;font-size: 30px; font-style: normal; font-weight: 500 ; border-radius: 14px; background: #1991FF; ");
		style1 = "border-radius: 14px;background: #2E3138; color: #1E86CF; font-family: Inter; font-size: 30px; font-style: normal ; font-weight:500;";
		style2 = "border-radius: 14px; background: #005DB2; color: #84C3FD;font-family: Inter;font-size: 30px;font-style: normal;font-weight: 500;line-height: normal; ";
		style3 = "border-radius: 10px; background: #005DB2; color: #84C3FD;font-family: Inter;font-size: 15px;font-style: normal;font-weight: 500;line-height: normal; ";
		style4 = "border-radius: 14px; background: #616161; color: #A0A1A2; font-family: Inter; font-size: 28px; ";
	}
	else // currently it's dark mode
	{
		ui.change_theme_btn->setStyleSheet("border-radius: 13px;\nbackground: #B2E3FF; color: #B2E3FF; \nfont-family: Inter;\n\n\n");
		ui.change_theme_btn->setText("dark");
		//Animation//
		ui.image_button->setStyleSheet(" background-image:url(:/Calculator_Qt/Screenshot 2023-07-08 020926.png); background-repeat: no-repeat; border-radius: 10px; font-family: Inter; ");
		Animation_2 = new QPropertyAnimation(ui.image_button, "geometry");
		Animation_2->setDuration(270);
		Animation_2->setStartValue(ui.image_button->geometry());
		Animation_2->setEndValue(QRect(10, 10, 24, 22));
		Animation_2->start();
		////////////////////////////
		ui.centralWidget->setStyleSheet("QPushButton::pressed{"
			"	background - color: rgb(188, 188, 188);"
		    "}"
			"QPushButton::hover{"
			"	background - color: #D2D2D2;"
			"}; "
		    "background - color: #FFFFFF; ");
		ui.screen1->setStyleSheet("border : none;\nbackground: transparent;\n \nfont-family: Inter;\nfont-size: 35px;\nfont-style: normal;\nfont-weight: 500;\nline-height: normal;");
		ui.textBrowser->setStyleSheet("border: none; background-color: #ffffff; color: #5C5B5B; font-family: Inter; font-size: 15px; font-style: normal; ");
		ui.history_btn->setStyleSheet("border-radius: 13px; background-image: url(:/Calculator_Qt/history icon 3.png);");
		ui.equal_btn->setStyleSheet("border-radius: 14px;\nbackground: #19ACFF;\n\ncolor: #CEE4F8;\nfont-family: Inter;\nfont-size: 30px;\nfont-style: normal;\nfont-weight: 500;\nline-height: normal;");
		style1 = style4 = "border-radius: 14px;\ncolor: #1E86CF;\nfont-family: Inter;\nfont-size: 30px;\nfont-style: normal;\nfont-weight: 500;\nline-height: normal;\n\n";
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

void Calculator_Qt::on_change_theme_btn_clicked()
{
	on_image_button_clicked();
}

void Calculator_Qt::on_screen1_textChanged()
{
	if (ui.screen1->text() == "")return;
	int length = ui.screen1->text().length();
	QChar newChar = ui.screen1->text()[length - 1];
	QString valid = "0123456789.+-*/^%()";
	if (valid.contains(newChar) || length >= 3 && ui.screen1->text()[length - 3] == 'a' || ui.screen1->text() == "Syntax Error" || ui.screen1->text() == "Math Error")
		return;
	else
		this->on_Del_btn_clicked();
}

void Calculator_Qt::testCases()
{
	// to enable this function call it in the constructor
	// write the test cases in the console
	// the test cases must be in this formate --> equation = answer

	std::string test, eq, sol;
	bool flag;
	for (int i = 0; i < 100; ++i)
	{
		eq = sol = "";
		flag = false;
		std::getline(std::cin, test);
		for (int j = 0; j < test.size(); ++j)
		{
			if (test[j] == ' ') {
				flag = true;
				j += 2;
				continue;
			}
			flag ? sol += test[j] : eq += test[j];
		}
		cout << "equation" << eq << " = " << sol << "\n";
		ui.screen1->setText(QString::fromStdString(eq));
		if (ans == this->Solve())
			cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<goood\n";
		else cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<baaad\n";

	}
}


void Calculator_Qt::on_history_btn_clicked()
{
	if (show_history == false)
	{
		Animation_3 = new QPropertyAnimation(this, "geometry");
		Animation_3->setDuration(350);
		Animation_3->setStartValue(geometry());
		Animation_3->setEndValue(QRect(x(), y()+30, 550, 562));
		Animation_3->start();
		show_history = true;
		
	}
	else
	{
		Animation_4 = new QPropertyAnimation(this, "geometry");
		Animation_4->setDuration(350);
		Animation_4->setStartValue(geometry());
		Animation_4->setEndValue(QRect(x(), y()+30, 300, 562));
		Animation_4->start();
		show_history = false;
	}
}
