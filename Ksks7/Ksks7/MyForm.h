#include <Winsock2.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <msclr/marshal_cppstd.h>
#include <ctime>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

struct Command {
    std::string comanda;
    std::vector<std::string> parameters;
};

struct Sprite {
    int index;
    int width;
    int height;
    std::vector<unsigned char> data;
};

std::vector<Sprite> sprites;


bool breakrules = false;
int who_paint = 0;

int orientir = 0;

std::string commanda = "";
int parameter[8];
int leng = 0;
std::string parameter2[1];
int leng2 = 0;
int paint_paint = 16;
int j = 0;

int rand_num = 0;
bool isrand = false;


namespace KSKS7 {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    /// <summary>
    /// Сводка для MyForm
    /// </summary>


    public ref class MyForm : public System::Windows::Forms::Form
    {
        System::Timers::Timer^ timer;
    private:
        UdpClient^ udpServer;
    private: System::Windows::Forms::Label^ label1;

    private: System::Windows::Forms::Panel^ panel1;
           int port = 12345;



    private: Bitmap^ Bit_map;
    public:
        MyForm(void)
        {
            InitializeComponent();
            //
            //TODO: добавьте код конструктора
            //
            udpServer = gcnew UdpClient(port);
            udpServer->BeginReceive(gcnew AsyncCallback(this, &MyForm::ReceiveCallback), nullptr);
            Bit_map = gcnew Bitmap(panel1->Width, panel1->Height);
        }
    private:
        void ReceiveCallback(IAsyncResult^ ar)
        {
            IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Any, port);
            array<Byte>^ receiveBytes = udpServer->EndReceive(ar, endPoint);
            String^ receivedMessage = Encoding::ASCII->GetString(receiveBytes);
            if (receivedMessage == "random")
            {
                isrand = true;
                std::cout << "1";
            }

            // Обработка полученного сообщения
            // Ваш код для обработки сообщения
            this->Invoke(gcnew Action<String^>(this, &MyForm::parsi), receivedMessage);
            // Продолжаем прослушивать порт
            udpServer->BeginReceive(gcnew AsyncCallback(this, &MyForm::ReceiveCallback), nullptr);
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::ComponentModel::IContainer^ components;
    protected:

    private:
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>


#pragma region Windows Form Designer generated code
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        ///
        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(12, 476);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(158, 27);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Пустая строка\r\n";
            // 
            // panel1
            // 
            this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panel1->Location = System::Drawing::Point(12, 12);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(749, 450);
            this->panel1->TabIndex = 2;
            this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(773, 552);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->label1);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->ResumeLayout(false);
            this->PerformLayout();

        }

        void DrawRoundedRectangle(Graphics^ g, Pen^ pen, int x, int y, int width, int height, int radius)
        {
            GraphicsPath^ path = gcnew GraphicsPath();

            System::Drawing::Rectangle rect = System::Drawing::Rectangle(x, y, width, height);

            int diameter = 2 * radius;
            System::Drawing::Rectangle arc = System::Drawing::Rectangle(rect.Location, System::Drawing::Size(diameter, diameter));

            path->AddArc(arc, 180, 90);
            arc.X = rect.Right - diameter;
            path->AddArc(arc, 270, 90);
            arc.Y = rect.Bottom - diameter;
            path->AddArc(arc, 0, 90);
            arc.X = rect.Left;
            path->AddArc(arc, 90, 90);

            path->CloseFigure();


            g->DrawPath(pen, path);

            delete path;
        }

        void FillRoundedRectangle(Graphics^ g, int x, int y, int width, int height, int radius, Color fillColor)
        {
            System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();

            System::Drawing::Rectangle rect = System::Drawing::Rectangle(x, y, width, height);

            int diameter = 2 * radius;
            System::Drawing::Rectangle arc = System::Drawing::Rectangle(rect.Location, System::Drawing::Size(diameter, diameter));

            path->AddArc(arc, 180, 90);
            arc.X = rect.Right - diameter;
            path->AddArc(arc, 270, 90);
            arc.Y = rect.Bottom - diameter;
            path->AddArc(arc, 0, 90);
            arc.X = rect.Left;
            path->AddArc(arc, 90, 90);

            path->CloseFigure();

            SolidBrush^ fillBrush = gcnew SolidBrush(fillColor);
            g->FillPath(fillBrush, path);

            delete path;
            delete fillBrush;
        }

        void Draw_Text(Graphics^ g, String^ text, Color textColor, int x, int y, int fonte, int len)
        {
            System::Drawing::Font^ font;
            switch (fonte)
            {
            case 1:
                font = gcnew System::Drawing::Font("Arial", len);
                break;
            case 2:
                font = gcnew System::Drawing::Font("Times New Roman", len);
                break;
            case 3:
                font = gcnew System::Drawing::Font("Courier New", len);
                break;
            case 4:
                font = gcnew System::Drawing::Font("Verdana", len);
                break;
            case 5:
                font = gcnew System::Drawing::Font("Tahoma", len);
                break;
            case 6:
                font = gcnew System::Drawing::Font("Comic Sans MS", len);
                break;
            default:
                breakrules = true;
                break;
            }
            System::Drawing::Brush^ brush = gcnew SolidBrush(textColor);
            Matrix^ rotationMatrix = gcnew Matrix();
            rotationMatrix->RotateAt(orientir, Point(x, y));

            g->Transform = rotationMatrix;
            g->DrawString(text, font, brush, x, y);
        }

        void Draw_Time(Graphics^ g, String^ text, Color textColor, int x, int y, int fonte, int len)
        {
            System::Drawing::Font^ font;
            switch (fonte)
            {
            case 1:
                font = gcnew System::Drawing::Font("Arial", len);
                break;
            case 2:
                font = gcnew System::Drawing::Font("Times New Roman", len);
                break;
            case 3:
                font = gcnew System::Drawing::Font("Courier New", len);
                break;
            case 4:
                font = gcnew System::Drawing::Font("Verdana", len);
                break;
            case 5:
                font = gcnew System::Drawing::Font("Tahoma", len);
                break;
            case 6:
                font = gcnew System::Drawing::Font("Comic Sans MS", len);
                break;
            default:
                breakrules = true;
                break;
            }
            System::Drawing::Brush^ brush = gcnew SolidBrush(textColor);

            panel1->BackColor = Color::White;
            g->DrawString(text, font, brush, x, y);
            panel1->Invalidate();

            int remainingTime = parameter[5];
            while (remainingTime >= 0) {
                // Обновляем текст с оставшимся временем
                text = "Remaining: " + remainingTime.ToString();
                g->Clear(panel1->BackColor); // Очистка фона
                g->DrawString(text, font, brush, x, y); // Отображение времени
                panel1->Invalidate();

                // Задержка на одну секунду
                System::Threading::Thread::Sleep(1000);

                remainingTime--;
            }
        }

        Color MyCol()
        {
            srand(time(0));
            if (isrand == true)
            {
                parameter[j] = ((rand() % 17) + 1);
            }
            if (1 == parameter[j])
            {
                return Color::Red;
            }
            else if (2 == parameter[j])
            {
                return Color::Blue;
            }
            else if (3 == parameter[j])
            {
                return Color::Black;
            }
            else if (4 == parameter[j])
            {
                return Color::Brown;
            }
            else if (5 == parameter[j])
            {
                return Color::Green;
            }
            else if (6 == parameter[j])
            {
                return Color::White;
            }
            else if (7 == parameter[j])
            {
                return Color::Cyan;
            }
            else if (8 == parameter[j])
            {
                return Color::Yellow;
            }
            else  if (9 == parameter[j])
            {
                return Color::Magenta;
            }
            else  if (10 == parameter[j])
            {
                return Color::Gray;
            }
            else if (11 == parameter[j])
            {
                return Color::LightGray;
            }
            else  if (12 == parameter[j])
            {
                return Color::DarkGray;
            }
            else if (13 == parameter[j])
            {
                return Color::Orange;
            }
            else if (14 == parameter[j])
            {
                return Color::Pink;
            }
            else if (15 == parameter[j])
            {
                return Color::Purple;
            }
            else {
                return Color::White;
                breakrules = true;
            }
        }

        void drawImage(Graphics^ g, int x0, int y0, int w, int h, array<Color>^ imageData)
        {
            for (int x = 0; x < w; x++)
            {
                for (int y = 0; y < h; y++)
                {
                    Color pixelColor = imageData[x + y * w];
                    SolidBrush^ brush = gcnew SolidBrush(pixelColor);
                    g->FillRectangle(brush, x0 + x, y0 + y, 1, 1);
                }
            }
        }

        void loading(int index, int width, int height, const std::vector<unsigned char>& data) {
            Sprite sprite;
            sprite.index = index;
            sprite.width = width;
            sprite.height = height;
            sprite.data = data;
            sprites.push_back(sprite);
        }
        void showing(int index, int x, int y) {
            for (const Sprite& sprite : sprites) {
                if (sprite.index == index) {
                    Bitmap^ spriteBitmap = gcnew Bitmap(sprite.width, sprite.height);

                    Graphics^ spriteGraphics = Graphics::FromImage(spriteBitmap);


                    System::Drawing::Rectangle destRect(x, y, sprite.width, sprite.height);
                    spriteGraphics->DrawImage(g, parameter[0], parameter[1], parameter[2], parameter[3], sprite.data);

                    Graphics^ panelGraphics = panel1->CreateGraphics();
                    panelGraphics->DrawImage(spriteBitmap, x, y);
                    delete spriteBitmap;
                    delete spriteGraphics;
                }
            }
        }


        void drawLetterA(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 20, y + 0);
            g->DrawLine(pen, x + 20, y + 0, x + 40, y + 100);
            g->DrawLine(pen, x + 5, y + 50, x + 40, y + 50);
        }
        void drawLetterB(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 0, y + 0, x + 40, y + 25);
            g->DrawLine(pen, x + 40, y + 25, x + 0, y + 50);

            g->DrawLine(pen, x + 0, y + 100, x + 40, y + 75);
            g->DrawLine(pen, x + 40, y + 75, x + 0, y + 50);

        }

        void drawLetterC(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterD(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 15, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 85, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 85, x + 40, y + 15);
        }
        void drawLetterE(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 30, y + 50, x + 0, y + 50);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterF(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 50, x + 0, y + 50);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterG(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 55);
            g->DrawLine(pen, x + 20, y + 55, x + 40, y + 55);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterH(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 50, x + 0, y + 50);
        }
        void drawLetterI(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
        }
        void drawLetterJ(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
        }
        void drawLetterK(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 0, y + 50, x + 40, y + 100);
            g->DrawLine(pen, x + 0, y + 50, x + 40, y + 0);
        }
        void drawLetterL(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x + 0, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 0, y + 100, x + 40, y + 100);
        }
        void drawLetterM(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);

            g->DrawLine(pen, x + 20, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 20, y + 100, x + 40, y + 0);
        }
        void drawLetterN(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);

            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 0);
        }
        void drawLetterO(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterP(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 0, y + 0, x + 40, y + 25);
            g->DrawLine(pen, x + 40, y + 25, x + 0, y + 50);
        }
        void drawLetterQ(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 80, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 80, x + 0, y + 80);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterR(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 0, y + 0, x + 40, y + 25);
            g->DrawLine(pen, x + 40, y + 25, x + 0, y + 50);
            g->DrawLine(pen, x + 0, y + 50, x + 40, y + 100);
        }
        void drawLetterS(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 50);
            g->DrawLine(pen, x + 40, y + 50, x + 0, y + 50);
            g->DrawLine(pen, x + 0, y + 50, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 0);
        }
        void drawLetterT(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x + 20, y + 100, x + 20, y + 0);
            g->DrawLine(pen, x + 0, y + 0, x + 40, y + 0);
        }
        void drawLetterU(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
        }
        void drawLetterV(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 0, x + 20, y + 100);
            g->DrawLine(pen, x + 20, y + 100, x + 40, y + 0);
        }
        void drawLetterW(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 0, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 40, y + 0);

            g->DrawLine(pen, x + 20, y + 0, x + 0, y + 100);
            g->DrawLine(pen, x + 20, y + 0, x + 40, y + 100);
        }
        void drawLetterX(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 100, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 0);
        }
        void drawLetterY(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x + 20, y + 50, x + 20, y + 100);
            g->DrawLine(pen, x + 20, y + 50, x + 0, y + 0);
            g->DrawLine(pen, x + 20, y + 50, x + 40, y + 0);
        }
        void drawLetterZ(int x, int y, Graphics^ g, Pen^ pen)
        {
            g->DrawLine(pen, x, y + 0, x + 40, y + 0);
            g->DrawLine(pen, x + 40, y + 100, x + 0, y + 100);
            g->DrawLine(pen, x + 40, y + 0, x + 0, y + 100);
        }

        void parsi(String^ my_mes)
        {
            leng = 0;
            leng2 = 0;
            std::string my_mes1 = msclr::interop::marshal_as<std::string>(my_mes);
            check_command(my_mes1);
            label1->Text = my_mes;

            if (breakrules == false)
            {
                if (isrand == true)
                {
                    String^ message2 = "";
                    message2 = msclr::interop::marshal_as<String^>(commanda);
                    for (int i = 0; i < leng; i++)
                    {
                        message2 += System::Convert::ToString(parameter[i]) + " ";
                    }
                    for (int i = 0; i < leng2; i++)
                    {
                        message2 += msclr::interop::marshal_as<String^>(parameter2[i]);
                    }
                }

                Color colorss = MyCol();

                Graphics^ g = Graphics::FromImage(Bit_map);
                Pen^ pen = gcnew Pen(colorss, 2);
                SolidBrush^ brush = gcnew SolidBrush(colorss);


                if (paint_paint == 1)
                {
                    Bit_map = gcnew Bitmap(panel1->Width, panel1->Height);
                    panel1->BackColor = colorss;
                    panel1->Invalidate();
                }

                if (paint_paint == 2) {

                    g->DrawLine(pen, parameter[0], parameter[1], parameter[0] + 1, parameter[1] + 1);

                }
                if (paint_paint == 3) {

                    g->DrawLine(pen, parameter[0], parameter[1], parameter[2], parameter[3]);
                }
                if (paint_paint == 4) {

                    g->DrawRectangle(pen, parameter[0], parameter[1], parameter[2], parameter[3]);
                }
                if (paint_paint == 5) {

                    g->FillRectangle(brush, parameter[0], parameter[1], parameter[2], parameter[3]);
                }
                if (paint_paint == 6) {

                    g->DrawEllipse(pen, parameter[0], parameter[1], parameter[2], parameter[3]);
                }
                if (paint_paint == 7) {

                    g->FillEllipse(brush, parameter[0], parameter[1], parameter[2], parameter[3]);
                }
                if (paint_paint == 8)
                {

                    g->DrawEllipse(pen, parameter[0], parameter[1], parameter[2], parameter[2]);
                }
                if (paint_paint == 9)
                {

                    g->FillEllipse(brush, parameter[0], parameter[1], parameter[2], parameter[2]);
                }
                if (paint_paint == 10)
                {
                    DrawRoundedRectangle(g, pen, parameter[0], parameter[1], parameter[2], parameter[3], parameter[4]);
                }
                if (paint_paint == 11)
                {
                    FillRoundedRectangle(g, parameter[0], parameter[1], parameter[2], parameter[3], parameter[4], colorss);
                }
                if (paint_paint == 12)
                {
                    String^ textToDraw = msclr::interop::marshal_as<String^>(parameter2[0]);
                    Draw_Text(g, textToDraw, colorss, parameter[0], parameter[1], parameter[3], parameter[4]);
                }
                if (paint_paint == 13)
                {
                    array<Color>^ imageData = gcnew array<Color>(parameter[2] * parameter[3]);

                    for (int i = 0; i < imageData->Length; i++)
                    {
                        imageData[i] = colorss;
                    }


                    drawImage(g, parameter[0], parameter[1], parameter[2], parameter[3], imageData);
                }
                if (paint_paint == 15)
                {
                    parameter2[0] = std::to_string(parameter[5]);
                    parameter2[0] = "Remaining: " + parameter2[0];
                    String^ textToDraw = msclr::interop::marshal_as<String^>(parameter2[0]);
                    Draw_Time(g, textToDraw, colorss, parameter[0], parameter[1], parameter[3], parameter[4]);
                }
                if (paint_paint == 17)
                {
                    orientir = parameter[0];
                }
                if (paint_paint == 18)
                {
                    Screen^ primaryScreen = Screen::PrimaryScreen;
                    int screenWidth = primaryScreen->Bounds.Width;
                    String^ textToDraw = "Width: " + screenWidth;
                    Draw_Text(g, textToDraw, Color::Black, 100, 50, 1, 16);
                }
                if (paint_paint == 19)
                {
                    Screen^ primaryScreen = Screen::PrimaryScreen;
                    int screenHeight = primaryScreen->Bounds.Height;
                    String^ textToDraw = "Height: " + screenHeight;
                    Draw_Text(g, textToDraw, Color::Black, 100, 100, 1, 16);
                }
                if (paint_paint == 16)
                {
                    std::string wordd = parameter2[0];
                    int x = parameter[0], y = parameter[1];
                    for (char letter : wordd) {
                        if (letter == 'A' || letter == 'a') {
                            drawLetterA(x, y, g, pen);
                        }
                        else if (letter == 'B' || letter == 'b') {
                            drawLetterB(x, y, g, pen);
                        }
                        else if (letter == 'C' || letter == 'c') {
                            drawLetterC(x, y, g, pen);
                        }
                        else if (letter == 'D' || letter == 'd') {
                            drawLetterD(x, y, g, pen);
                        }
                        else if (letter == 'E' || letter == 'e') {
                            drawLetterE(x, y, g, pen);
                        }
                        else if (letter == 'F' || letter == 'f') {
                            drawLetterF(x, y, g, pen);
                        }
                        else if (letter == 'G' || letter == 'g') {
                            drawLetterG(x, y, g, pen);
                        }
                        else if (letter == 'H' || letter == 'h') {
                            drawLetterH(x, y, g, pen);
                        }
                        else if (letter == 'I' || letter == 'i') {
                            drawLetterI(x, y, g, pen);
                        }
                        else if (letter == 'J' || letter == 'j') {
                            drawLetterJ(x, y, g, pen);
                        }
                        else if (letter == 'K' || letter == 'k') {
                            drawLetterK(x, y, g, pen);
                        }
                        else if (letter == 'L' || letter == 'l') {
                            drawLetterL(x, y, g, pen);
                        }
                        else if (letter == 'M' || letter == 'm') {
                            drawLetterM(x, y, g, pen);
                        }
                        else if (letter == 'N' || letter == 'n') {
                            drawLetterN(x, y, g, pen);
                        }
                        else if (letter == 'O' || letter == 'o') {
                            drawLetterO(x, y, g, pen);
                        }
                        else if (letter == 'P' || letter == 'p') {
                            drawLetterP(x, y, g, pen);
                        }
                        else if (letter == 'Q' || letter == 'q') {
                            drawLetterQ(x, y, g, pen);
                        }
                        else if (letter == 'R' || letter == 'r') {
                            drawLetterR(x, y, g, pen);
                        }
                        else if (letter == 'S' || letter == 's') {
                            drawLetterS(x, y, g, pen);
                        }
                        else if (letter == 'T' || letter == 't') {
                            drawLetterT(x, y, g, pen);
                        }
                        else if (letter == 'U' || letter == 'u') {
                            drawLetterU(x, y, g, pen);
                        }
                        else if (letter == 'V' || letter == 'v') {
                            drawLetterV(x, y, g, pen);
                        }
                        else if (letter == 'W' || letter == 'w') {
                            drawLetterW(x, y, g, pen);
                        }
                        else if (letter == 'X' || letter == 'x') {
                            drawLetterX(x, y, g, pen);
                        }
                        else if (letter == 'Y' || letter == 'y') {
                            drawLetterY(x, y, g, pen);
                        }
                        else if (letter == 'Z' || letter == 'z') {
                            drawLetterZ(x, y, g, pen);
                        }
                        x += 60;
                    }
                }
                if (paint_paint == 20)
                {
                    loading(parameter[0], parameter[0], parameter[0], Sprite.data);
                }
                if (paint_paint == 21)
                {
                    showing(parameter[0], parameter[0], parameter[0]);
                }

                delete g;
                delete pen;
                delete brush;

                panel1->Invalidate();
                paint_paint = 0;
            }
            else {
                label1->Text = "Ошибка! Неверная команда!";
            }
            isrand = false;
        }


        Command check_command(const std::string& commandStr) {
            srand(time(0));
            if (isrand == true)
            {
                rand_num = ((rand() % 13) + 1);
            }
            Command command;

            int number;
            who_paint = 0;
            int i = 0;

            std::istringstream get_mes_word(commandStr);
            std::string get_word;
            get_mes_word >> command.comanda;


            while (get_mes_word >> get_word) {
                if (get_word == ":")
                {
                    break;
                }
                command.comanda += " " + get_word;
            }
            if (command.comanda == "clear display" || rand_num == 1) {
                j = 0;
                paint_paint = 1;
                who_paint = 1;
            }
            if (command.comanda == "draw pixel" || rand_num == 2) {
                j = 2;
                paint_paint = 2;
                who_paint = 10;
            }
            if (command.comanda == "draw line" || rand_num == 3) {
                j = 4;
                paint_paint = 3;
                who_paint = 20;
            }
            if (command.comanda == "draw rectangle" || rand_num == 4)
            {
                j = 4;
                paint_paint = 4;
                who_paint = 30;
            }
            if (command.comanda == "fill rectangle" || rand_num == 5) {
                j = 4;
                paint_paint = 5;
                who_paint = 40;
            }
            if (command.comanda == "draw ellipse" || rand_num == 6) {
                j = 4;
                paint_paint = 6;
                who_paint = 50;
            }
            if (command.comanda == "fill ellipse" || rand_num == 7)
            {
                j = 4;
                paint_paint = 7;
                who_paint = 60;
            }
            if (command.comanda == "draw circle" || rand_num == 8)
            {
                j = 3;
                paint_paint = 8;
                who_paint = 70;
            }
            if (command.comanda == "fill circle" || rand_num == 9)
            {
                j = 3;
                paint_paint = 9;
                who_paint = 80;
            }
            if (command.comanda == "draw rounded rectangle" || rand_num == 10)
            {
                j = 5;
                paint_paint = 10;
                who_paint = 90;
            }
            if (command.comanda == "fill rounded rectangle" || rand_num == 11)
            {
                j = 5;
                paint_paint = 11;
                who_paint = 100;
            }
            if (command.comanda == "draw text" || rand_num == 12)
            {
                j = 2;
                paint_paint = 12;
                who_paint = 110;
            }
            if (command.comanda == "draw image" || rand_num == 13)
            {
                j = 4;
                paint_paint = 13;
                who_paint = 120;
            }
            if (command.comanda == "draw timer" || rand_num == 15)
            {
                j = 2;
                paint_paint = 15;
                who_paint = 150;
            }
            if (command.comanda == "draw letter")
            {
                j = 2;
                paint_paint = 16;
                who_paint = 160;
            }
            if (command.comanda == "load sprite")
            {
                paint_paint = 20;
                who_paint = 170;
            }
            if (command.comanda == "show sprite")
            {
                paint_paint = 21;
                who_paint = 180;
            }

            if (command.comanda == "get width")
            {
                paint_paint = 18;
                who_paint = 361;
            }
            if (command.comanda == "get height")
            {
                paint_paint = 19;
                who_paint = 361;
            }
            if (command.comanda == "set orientation")
            {
                who_paint = 360;
                paint_paint = 17;
            }

            if (who_paint == 0) {
                breakrules = true;
                return command;
            }
            if (isrand == true)
            {
                for (int i = 0; i < 8; i++)
                {
                    parameter[i] = rand() % 200;
                }
            }

            if (isrand == false)
            {
                if (!breakrules)
                {
                    while (get_mes_word >> get_word) {
                        if (who_paint == 1 || who_paint >= 10 && who_paint <= 12 || who_paint >= 20 && who_paint <= 24 || who_paint >= 30 && who_paint <= 34
                            || who_paint >= 40 && who_paint <= 44 || who_paint >= 50 && who_paint <= 54 || who_paint >= 60 && who_paint <= 64 || who_paint >= 70 && who_paint <= 73
                            || who_paint >= 80 && who_paint <= 83 || who_paint >= 90 && who_paint <= 95 || who_paint >= 100 && who_paint <= 105 || who_paint >= 110 && who_paint <= 115
                            || who_paint >= 120 && who_paint <= 124 || who_paint >= 150 && who_paint <= 155 || who_paint >= 160 && who_paint <= 163 || who_paint >= 170 && who_paint <= 173 ||
                            who_paint >= 180 && who_paint <= 182 ||
                            who_paint == 360)
                        {
                            command.parameters.push_back(get_word);
                            if (who_paint == 115 || who_paint == 163)
                            {
                                parameter2[0] = get_word;
                                breakrules = false;
                                return command;
                            }
                            try {
                                number = stoi(get_word);
                                parameter[i] = number;
                                i++;
                            }
                            catch (const std::invalid_argument& e) {
                                breakrules = true;
                                return command;
                            }
                            breakrules = false;
                            who_paint++;
                        }
                    }
                    breakrules = false;
                    return command;
                }
                else {
                    return command;
                }
            }
            return command;
        }


        void mes_get(String^ message) {

        }
#pragma endregion


    private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        e->Graphics->DrawImage(Bit_map, 0, 0);
    }
    };
}
