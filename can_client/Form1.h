#pragma once

#include "include/Usbcan32.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using System::Windows::Forms::Message;

namespace can_client {

	extern unsigned char data[8];
	extern tCanMsgStruct TxCanMsg_l;

	/// <summary>
	/// Сводка для Form1
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			m_fIsInitialized = FALSE;
			can_init();

			// чтение таблицы из файла
			String^ myXMLfile = "C:/workspace/can_client/can_client/can_parameters.xml";
			DataSet^ ds = gcnew DataSet("can_parameters");
			try
			{
				ds->ReadXml(myXMLfile);
				//bindingSource1->DataSource = ds->Tables[0];
				ParametersDataGrid->DataSource = ds->Tables[0];
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->ToString());
			}

			eng = new CC_VEngine;
			nMessage = 0;
			isLogWrite = 0;
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			delete eng;
			if (components)
			{
				delete components;
			}
		}
	private: DataTable^ paramDataTable;
	private: System::Windows::Forms::Button^  initButton;




































	private: System::Windows::Forms::Button^  sendButton;



















































































private: System::Windows::Forms::TextBox^  textId2;
private: System::Windows::Forms::TextBox^  textId1;
private: System::Windows::Forms::TextBox^  textRandOut;
private: System::Windows::Forms::TextBox^  textRandIn;

private: System::Windows::Forms::Button^  buttonRandOut;
private: System::Windows::Forms::Button^  buttonRandIn;




















































private: System::Windows::Forms::Button^  writeLogButton;
private: System::Windows::Forms::TextBox^  logFileName;
private: System::Windows::Forms::CheckBox^  logCheck;













private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::Label^  label27;




































private: System::Data::DataSet^  canParametersDataSet;



private: System::Windows::Forms::BindingSource^  bindingSource1;
private: System::Windows::Forms::TabPage^  tabParameters;
private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::TextBox^  FilterTextBox;
private: System::Windows::Forms::DataGridView^  ParametersDataGrid;
private: System::Windows::Forms::TabControl^  tabControl1;
private: System::Windows::Forms::TabPage^  tabControlPage;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::GroupBox^  groupBox4;
private: System::Windows::Forms::GroupBox^  groupBox3;
private: System::Windows::Forms::GroupBox^  groupBox2;
private: System::Windows::Forms::TabControl^  tctrlModeParameters;
private: System::Windows::Forms::TabPage^  tab1_Standby;
private: System::Windows::Forms::TabPage^  tab2_Period;



private: System::Windows::Forms::RadioButton^  radioButton4;
private: System::Windows::Forms::RadioButton^  radioButton3;
private: System::Windows::Forms::RadioButton^  radioButton2;
private: System::Windows::Forms::RadioButton^  radioButton1;
private: System::Windows::Forms::Button^  ApplyPID;


private: System::Windows::Forms::Button^  butApplyMode;
private: System::Windows::Forms::TabPage^  tab3_TimeSet;
private: System::Windows::Forms::TabPage^  tab4_PID;


private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::TextBox^  tbCurrentMode;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::TextBox^  NCurrentValue;


private: System::Windows::Forms::NumericUpDown^  Nmax;

private: System::Windows::Forms::NumericUpDown^  Nmin;
private: System::Windows::Forms::ProgressBar^  NCurrentProgress;


private: System::Windows::Forms::Label^  label3;

private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::CheckBox^  checkBox3;
private: System::Windows::Forms::TextBox^  QCCurrentValue;
private: System::Windows::Forms::NumericUpDown^  QCmax;
private: System::Windows::Forms::NumericUpDown^  QCmin;



private: System::Windows::Forms::ProgressBar^  QCCurrentProgress;

private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::CheckBox^  PMFailureCheck;

private: System::Windows::Forms::TextBox^  PMCurrentValue;

private: System::Windows::Forms::NumericUpDown^  PMmax;

private: System::Windows::Forms::NumericUpDown^  PMmin;
private: System::Windows::Forms::ProgressBar^  PMCurrentProgress;


private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::CheckBox^  NFailureCheck;

private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::NumericUpDown^  numericUpDown11;
private: System::Windows::Forms::NumericUpDown^  numericUpDown12;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::NumericUpDown^  numericUpDown9;
private: System::Windows::Forms::NumericUpDown^  numericUpDown10;
private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::NumericUpDown^  numericUpDown8;
private: System::Windows::Forms::NumericUpDown^  numericUpDown7;
private: System::Windows::Forms::Label^  label31;
private: System::Windows::Forms::Label^  label32;
private: System::Windows::Forms::Label^  label30;
private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::Label^  label25;
private: System::Windows::Forms::Label^  label24;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::CheckBox^  checkBox6;
private: System::Windows::Forms::CheckBox^  checkBox5;
private: System::Windows::Forms::CheckBox^  checkBox4;

private: System::Windows::Forms::TextBox^  textBox4;
private: System::Windows::Forms::Label^  label33;
private: System::Windows::Forms::Label^  label34;
private: System::Windows::Forms::TextBox^  textBox5;
private: System::Windows::Forms::Label^  label35;
private: System::Windows::Forms::TextBox^  textBox6;
private: System::Windows::Forms::Label^  label36;
private: System::Windows::Forms::TextBox^  textBox7;
private: System::Windows::Forms::Label^  label42;
private: System::Windows::Forms::TextBox^  NCurrent;


private: System::Windows::Forms::Label^  label41;
private: System::Windows::Forms::Label^  label40;
private: System::Windows::Forms::Label^  label39;
private: System::Windows::Forms::Label^  label38;
private: System::Windows::Forms::Label^  label37;
private: System::Windows::Forms::TextBox^  NSetpoint;

private: System::Windows::Forms::TextBox^  KdMult;

private: System::Windows::Forms::TextBox^  KdVal;
private: System::Windows::Forms::TextBox^  KiMult;



private: System::Windows::Forms::TextBox^  KiVal;
private: System::Windows::Forms::TextBox^  KpMult;


private: System::Windows::Forms::TextBox^  KpVal;

private: System::Windows::Forms::Label^  label45;
private: System::Windows::Forms::Label^  label44;
private: System::Windows::Forms::Label^  label43;
private: System::Windows::Forms::Button^  ApplyPeriodic;

private: System::Windows::Forms::Button^  ApplyTimeSet;
private: System::Windows::Forms::Label^  label46;
private: System::Windows::Forms::TextBox^  textBox8;

private: System::Windows::Forms::Label^  label48;
private: System::Windows::Forms::TextBox^  textBox10;

private: System::Windows::Forms::Label^  label47;
private: System::Windows::Forms::TextBox^  textBox9;


private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::Label^  label50;
private: System::Windows::Forms::Label^  label49;
private: System::Windows::Forms::ComboBox^  comboBox2;
private: System::Windows::Forms::ComboBox^  comboBox3;
private: System::Windows::Forms::ComboBox^  comboBox1;
private: System::Windows::Forms::ComboBox^  comboBox4;
private: System::Windows::Forms::ListView^  listView1;



private: System::ComponentModel::IContainer^  components;























	protected: 

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L"с"));
			System::Windows::Forms::ListViewItem^  listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(L"мс"));
			System::Windows::Forms::ListViewItem^  listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(L"мкс"));
			this->initButton = (gcnew System::Windows::Forms::Button());
			this->bindingSource1 = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->textId2 = (gcnew System::Windows::Forms::TextBox());
			this->textId1 = (gcnew System::Windows::Forms::TextBox());
			this->textRandOut = (gcnew System::Windows::Forms::TextBox());
			this->textRandIn = (gcnew System::Windows::Forms::TextBox());
			this->buttonRandOut = (gcnew System::Windows::Forms::Button());
			this->buttonRandIn = (gcnew System::Windows::Forms::Button());
			this->canParametersDataSet = (gcnew System::Data::DataSet());
			this->sendButton = (gcnew System::Windows::Forms::Button());
			this->writeLogButton = (gcnew System::Windows::Forms::Button());
			this->logFileName = (gcnew System::Windows::Forms::TextBox());
			this->logCheck = (gcnew System::Windows::Forms::CheckBox());
			this->tabParameters = (gcnew System::Windows::Forms::TabPage());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->FilterTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ParametersDataGrid = (gcnew System::Windows::Forms::DataGridView());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabControlPage = (gcnew System::Windows::Forms::TabPage());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->tctrlModeParameters = (gcnew System::Windows::Forms::TabControl());
			this->tab1_Standby = (gcnew System::Windows::Forms::TabPage());
			this->tab2_Period = (gcnew System::Windows::Forms::TabPage());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->butApplyMode = (gcnew System::Windows::Forms::Button());
			this->ApplyPID = (gcnew System::Windows::Forms::Button());
			this->tab3_TimeSet = (gcnew System::Windows::Forms::TabPage());
			this->tab4_PID = (gcnew System::Windows::Forms::TabPage());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tbCurrentMode = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->NCurrentProgress = (gcnew System::Windows::Forms::ProgressBar());
			this->Nmin = (gcnew System::Windows::Forms::NumericUpDown());
			this->Nmax = (gcnew System::Windows::Forms::NumericUpDown());
			this->NCurrentValue = (gcnew System::Windows::Forms::TextBox());
			this->NFailureCheck = (gcnew System::Windows::Forms::CheckBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->PMFailureCheck = (gcnew System::Windows::Forms::CheckBox());
			this->PMCurrentValue = (gcnew System::Windows::Forms::TextBox());
			this->PMmax = (gcnew System::Windows::Forms::NumericUpDown());
			this->PMmin = (gcnew System::Windows::Forms::NumericUpDown());
			this->PMCurrentProgress = (gcnew System::Windows::Forms::ProgressBar());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->QCCurrentValue = (gcnew System::Windows::Forms::TextBox());
			this->QCmax = (gcnew System::Windows::Forms::NumericUpDown());
			this->QCmin = (gcnew System::Windows::Forms::NumericUpDown());
			this->QCCurrentProgress = (gcnew System::Windows::Forms::ProgressBar());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown7 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown8 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown9 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown10 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown11 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown12 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->KpVal = (gcnew System::Windows::Forms::TextBox());
			this->KpMult = (gcnew System::Windows::Forms::TextBox());
			this->KiVal = (gcnew System::Windows::Forms::TextBox());
			this->KiMult = (gcnew System::Windows::Forms::TextBox());
			this->KdVal = (gcnew System::Windows::Forms::TextBox());
			this->KdMult = (gcnew System::Windows::Forms::TextBox());
			this->NSetpoint = (gcnew System::Windows::Forms::TextBox());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->NCurrent = (gcnew System::Windows::Forms::TextBox());
			this->label43 = (gcnew System::Windows::Forms::Label());
			this->label44 = (gcnew System::Windows::Forms::Label());
			this->label45 = (gcnew System::Windows::Forms::Label());
			this->ApplyTimeSet = (gcnew System::Windows::Forms::Button());
			this->ApplyPeriodic = (gcnew System::Windows::Forms::Button());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label46 = (gcnew System::Windows::Forms::Label());
			this->label47 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->label48 = (gcnew System::Windows::Forms::Label());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label49 = (gcnew System::Windows::Forms::Label());
			this->label50 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bindingSource1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->canParametersDataSet))->BeginInit();
			this->tabParameters->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ParametersDataGrid))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabControlPage->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->tctrlModeParameters->SuspendLayout();
			this->tab1_Standby->SuspendLayout();
			this->tab2_Period->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tab3_TimeSet->SuspendLayout();
			this->tab4_PID->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Nmin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Nmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PMmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PMmin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->QCmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->QCmin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown12))->BeginInit();
			this->SuspendLayout();
			// 
			// initButton
			// 
			this->initButton->Location = System::Drawing::Point(18, 46);
			this->initButton->Name = L"initButton";
			this->initButton->Size = System::Drawing::Size(91, 30);
			this->initButton->TabIndex = 0;
			this->initButton->Text = L"Инициализировать";
			this->initButton->UseVisualStyleBackColor = true;
			this->initButton->Click += gcnew System::EventHandler(this, &Form1::initButton_Click);
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(64, 133);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(91, 13);
			this->label28->TabIndex = 44;
			this->label28->Text = L"id подпараметра";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(64, 107);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(73, 13);
			this->label27->TabIndex = 43;
			this->label27->Text = L"id параметра";
			// 
			// textId2
			// 
			this->textId2->Location = System::Drawing::Point(17, 130);
			this->textId2->Name = L"textId2";
			this->textId2->Size = System::Drawing::Size(41, 20);
			this->textId2->TabIndex = 38;
			this->textId2->Text = L"0";
			// 
			// textId1
			// 
			this->textId1->Location = System::Drawing::Point(18, 104);
			this->textId1->Name = L"textId1";
			this->textId1->Size = System::Drawing::Size(40, 20);
			this->textId1->TabIndex = 37;
			this->textId1->Text = L"0";
			// 
			// textRandOut
			// 
			this->textRandOut->Location = System::Drawing::Point(17, 187);
			this->textRandOut->Name = L"textRandOut";
			this->textRandOut->Size = System::Drawing::Size(100, 20);
			this->textRandOut->TabIndex = 36;
			this->textRandOut->Text = L"0";
			// 
			// textRandIn
			// 
			this->textRandIn->Location = System::Drawing::Point(17, 157);
			this->textRandIn->Name = L"textRandIn";
			this->textRandIn->Size = System::Drawing::Size(100, 20);
			this->textRandIn->TabIndex = 35;
			this->textRandIn->Text = L"0";
			// 
			// buttonRandOut
			// 
			this->buttonRandOut->Location = System::Drawing::Point(135, 184);
			this->buttonRandOut->Name = L"buttonRandOut";
			this->buttonRandOut->Size = System::Drawing::Size(75, 23);
			this->buttonRandOut->TabIndex = 33;
			this->buttonRandOut->Text = L"Отправить";
			this->buttonRandOut->UseVisualStyleBackColor = true;
			this->buttonRandOut->Click += gcnew System::EventHandler(this, &Form1::buttonRandOut_Click);
			// 
			// buttonRandIn
			// 
			this->buttonRandIn->Location = System::Drawing::Point(135, 155);
			this->buttonRandIn->Name = L"buttonRandIn";
			this->buttonRandIn->Size = System::Drawing::Size(75, 23);
			this->buttonRandIn->TabIndex = 32;
			this->buttonRandIn->Text = L"Запрос";
			this->buttonRandIn->UseVisualStyleBackColor = true;
			this->buttonRandIn->Click += gcnew System::EventHandler(this, &Form1::buttonRandIn_Click);
			// 
			// canParametersDataSet
			// 
			this->canParametersDataSet->DataSetName = L"can_parameters";
			// 
			// sendButton
			// 
			this->sendButton->Location = System::Drawing::Point(117, 46);
			this->sendButton->Name = L"sendButton";
			this->sendButton->Size = System::Drawing::Size(82, 30);
			this->sendButton->TabIndex = 27;
			this->sendButton->Text = L"отправить";
			this->sendButton->UseVisualStyleBackColor = true;
			this->sendButton->Click += gcnew System::EventHandler(this, &Form1::sendButton_Click);
			// 
			// writeLogButton
			// 
			this->writeLogButton->Location = System::Drawing::Point(18, 326);
			this->writeLogButton->Name = L"writeLogButton";
			this->writeLogButton->Size = System::Drawing::Size(75, 23);
			this->writeLogButton->TabIndex = 28;
			this->writeLogButton->Text = L"Писать лог";
			this->writeLogButton->UseVisualStyleBackColor = true;
			this->writeLogButton->Click += gcnew System::EventHandler(this, &Form1::writeLogButton_Click);
			// 
			// logFileName
			// 
			this->logFileName->Location = System::Drawing::Point(18, 355);
			this->logFileName->Name = L"logFileName";
			this->logFileName->Size = System::Drawing::Size(75, 20);
			this->logFileName->TabIndex = 30;
			// 
			// logCheck
			// 
			this->logCheck->AutoSize = true;
			this->logCheck->Enabled = false;
			this->logCheck->Location = System::Drawing::Point(18, 382);
			this->logCheck->Name = L"logCheck";
			this->logCheck->Size = System::Drawing::Size(91, 17);
			this->logCheck->TabIndex = 31;
			this->logCheck->Text = L"Лог пишется";
			this->logCheck->UseVisualStyleBackColor = true;
			// 
			// tabParameters
			// 
			this->tabParameters->Controls->Add(this->label29);
			this->tabParameters->Controls->Add(this->FilterTextBox);
			this->tabParameters->Controls->Add(this->ParametersDataGrid);
			this->tabParameters->Location = System::Drawing::Point(4, 22);
			this->tabParameters->Name = L"tabParameters";
			this->tabParameters->Padding = System::Windows::Forms::Padding(3);
			this->tabParameters->Size = System::Drawing::Size(947, 484);
			this->tabParameters->TabIndex = 3;
			this->tabParameters->Text = L"Таблица параметров";
			this->tabParameters->UseVisualStyleBackColor = true;
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(113, 9);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(47, 13);
			this->label29->TabIndex = 46;
			this->label29->Text = L"Фильтр";
			this->label29->Click += gcnew System::EventHandler(this, &Form1::label29_Click_1);
			// 
			// FilterTextBox
			// 
			this->FilterTextBox->Location = System::Drawing::Point(6, 6);
			this->FilterTextBox->Name = L"FilterTextBox";
			this->FilterTextBox->Size = System::Drawing::Size(101, 20);
			this->FilterTextBox->TabIndex = 45;
			this->FilterTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// ParametersDataGrid
			// 
			this->ParametersDataGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::DisplayedCells;
			this->ParametersDataGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->ParametersDataGrid->Location = System::Drawing::Point(3, 32);
			this->ParametersDataGrid->Name = L"ParametersDataGrid";
			this->ParametersDataGrid->ReadOnly = true;
			this->ParametersDataGrid->Size = System::Drawing::Size(944, 594);
			this->ParametersDataGrid->TabIndex = 0;
			this->ParametersDataGrid->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::ParametersDataGrid_CellClick);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabControlPage);
			this->tabControl1->Controls->Add(this->tabParameters);
			this->tabControl1->Location = System::Drawing::Point(216, 7);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(955, 510);
			this->tabControl1->TabIndex = 1;
			// 
			// tabControlPage
			// 
			this->tabControlPage->Controls->Add(this->groupBox4);
			this->tabControlPage->Controls->Add(this->groupBox3);
			this->tabControlPage->Controls->Add(this->groupBox2);
			this->tabControlPage->Controls->Add(this->groupBox1);
			this->tabControlPage->Location = System::Drawing::Point(4, 22);
			this->tabControlPage->Name = L"tabControlPage";
			this->tabControlPage->Padding = System::Windows::Forms::Padding(3);
			this->tabControlPage->Size = System::Drawing::Size(947, 484);
			this->tabControlPage->TabIndex = 4;
			this->tabControlPage->Text = L"Экран управления";
			this->tabControlPage->UseVisualStyleBackColor = true;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->comboBox2);
			this->groupBox4->Controls->Add(this->label13);
			this->groupBox4->Controls->Add(this->checkBox6);
			this->groupBox4->Controls->Add(this->checkBox5);
			this->groupBox4->Controls->Add(this->checkBox4);
			this->groupBox4->Controls->Add(this->label14);
			this->groupBox4->Controls->Add(this->label15);
			this->groupBox4->Controls->Add(this->label16);
			this->groupBox4->Controls->Add(this->checkBox3);
			this->groupBox4->Controls->Add(this->QCCurrentValue);
			this->groupBox4->Controls->Add(this->QCmax);
			this->groupBox4->Controls->Add(this->QCmin);
			this->groupBox4->Controls->Add(this->QCCurrentProgress);
			this->groupBox4->Controls->Add(this->label17);
			this->groupBox4->Controls->Add(this->label8);
			this->groupBox4->Controls->Add(this->label9);
			this->groupBox4->Controls->Add(this->label10);
			this->groupBox4->Controls->Add(this->label11);
			this->groupBox4->Controls->Add(this->PMFailureCheck);
			this->groupBox4->Controls->Add(this->PMCurrentValue);
			this->groupBox4->Controls->Add(this->PMmax);
			this->groupBox4->Controls->Add(this->PMmin);
			this->groupBox4->Controls->Add(this->PMCurrentProgress);
			this->groupBox4->Controls->Add(this->label12);
			this->groupBox4->Controls->Add(this->label7);
			this->groupBox4->Controls->Add(this->label6);
			this->groupBox4->Controls->Add(this->label5);
			this->groupBox4->Controls->Add(this->label4);
			this->groupBox4->Controls->Add(this->NFailureCheck);
			this->groupBox4->Controls->Add(this->NCurrentValue);
			this->groupBox4->Controls->Add(this->Nmax);
			this->groupBox4->Controls->Add(this->Nmin);
			this->groupBox4->Controls->Add(this->NCurrentProgress);
			this->groupBox4->Controls->Add(this->label3);
			this->groupBox4->Location = System::Drawing::Point(277, 239);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(625, 231);
			this->groupBox4->TabIndex = 3;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Графические индикаторы";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->tctrlModeParameters);
			this->groupBox3->Location = System::Drawing::Point(277, 17);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(625, 216);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Настройка режима работы";
			// 
			// tctrlModeParameters
			// 
			this->tctrlModeParameters->Controls->Add(this->tab1_Standby);
			this->tctrlModeParameters->Controls->Add(this->tab2_Period);
			this->tctrlModeParameters->Controls->Add(this->tab3_TimeSet);
			this->tctrlModeParameters->Controls->Add(this->tab4_PID);
			this->tctrlModeParameters->Location = System::Drawing::Point(9, 19);
			this->tctrlModeParameters->Name = L"tctrlModeParameters";
			this->tctrlModeParameters->SelectedIndex = 0;
			this->tctrlModeParameters->Size = System::Drawing::Size(592, 185);
			this->tctrlModeParameters->TabIndex = 0;
			// 
			// tab1_Standby
			// 
			this->tab1_Standby->Controls->Add(this->label33);
			this->tab1_Standby->Controls->Add(this->textBox4);
			this->tab1_Standby->Location = System::Drawing::Point(4, 22);
			this->tab1_Standby->Name = L"tab1_Standby";
			this->tab1_Standby->Padding = System::Windows::Forms::Padding(3);
			this->tab1_Standby->Size = System::Drawing::Size(584, 159);
			this->tab1_Standby->TabIndex = 0;
			this->tab1_Standby->Text = L"Ожидание";
			this->tab1_Standby->UseVisualStyleBackColor = true;
			// 
			// tab2_Period
			// 
			this->tab2_Period->Controls->Add(this->comboBox3);
			this->tab2_Period->Controls->Add(this->comboBox1);
			this->tab2_Period->Controls->Add(this->label48);
			this->tab2_Period->Controls->Add(this->textBox10);
			this->tab2_Period->Controls->Add(this->label47);
			this->tab2_Period->Controls->Add(this->textBox9);
			this->tab2_Period->Controls->Add(this->ApplyPeriodic);
			this->tab2_Period->Controls->Add(this->label34);
			this->tab2_Period->Controls->Add(this->textBox5);
			this->tab2_Period->Location = System::Drawing::Point(4, 22);
			this->tab2_Period->Name = L"tab2_Period";
			this->tab2_Period->Padding = System::Windows::Forms::Padding(3);
			this->tab2_Period->Size = System::Drawing::Size(584, 159);
			this->tab2_Period->TabIndex = 1;
			this->tab2_Period->Text = L"Периодический впрыск";
			this->tab2_Period->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label50);
			this->groupBox2->Controls->Add(this->label49);
			this->groupBox2->Controls->Add(this->label31);
			this->groupBox2->Controls->Add(this->label32);
			this->groupBox2->Controls->Add(this->label30);
			this->groupBox2->Controls->Add(this->label26);
			this->groupBox2->Controls->Add(this->label25);
			this->groupBox2->Controls->Add(this->label24);
			this->groupBox2->Controls->Add(this->label23);
			this->groupBox2->Controls->Add(this->label22);
			this->groupBox2->Controls->Add(this->label21);
			this->groupBox2->Controls->Add(this->label20);
			this->groupBox2->Controls->Add(this->numericUpDown11);
			this->groupBox2->Controls->Add(this->numericUpDown12);
			this->groupBox2->Controls->Add(this->label19);
			this->groupBox2->Controls->Add(this->numericUpDown9);
			this->groupBox2->Controls->Add(this->numericUpDown10);
			this->groupBox2->Controls->Add(this->label18);
			this->groupBox2->Controls->Add(this->numericUpDown8);
			this->groupBox2->Controls->Add(this->numericUpDown7);
			this->groupBox2->Location = System::Drawing::Point(17, 239);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(239, 231);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Параметры впрыска";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->tbCurrentMode);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->butApplyMode);
			this->groupBox1->Controls->Add(this->radioButton4);
			this->groupBox1->Controls->Add(this->radioButton3);
			this->groupBox1->Controls->Add(this->radioButton2);
			this->groupBox1->Controls->Add(this->radioButton1);
			this->groupBox1->Location = System::Drawing::Point(17, 17);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(239, 216);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Режим работы";
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(19, 154);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(130, 17);
			this->radioButton4->TabIndex = 3;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"Управление по ПИД";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(19, 133);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(173, 17);
			this->radioButton3->TabIndex = 2;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Задание продолжительности";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(19, 110);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(145, 17);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Периодический впрыск";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(19, 87);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(187, 17);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Ожидание (впрыск отсутствует)";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// butApplyMode
			// 
			this->butApplyMode->Location = System::Drawing::Point(19, 177);
			this->butApplyMode->Name = L"butApplyMode";
			this->butApplyMode->Size = System::Drawing::Size(75, 27);
			this->butApplyMode->TabIndex = 4;
			this->butApplyMode->Text = L"Применить";
			this->butApplyMode->UseVisualStyleBackColor = true;
			// 
			// ApplyPID
			// 
			this->ApplyPID->Location = System::Drawing::Point(259, 128);
			this->ApplyPID->Name = L"ApplyPID";
			this->ApplyPID->Size = System::Drawing::Size(86, 25);
			this->ApplyPID->TabIndex = 1;
			this->ApplyPID->Text = L"Применить";
			this->ApplyPID->UseVisualStyleBackColor = true;
			// 
			// tab3_TimeSet
			// 
			this->tab3_TimeSet->Controls->Add(this->listView1);
			this->tab3_TimeSet->Controls->Add(this->comboBox4);
			this->tab3_TimeSet->Controls->Add(this->label46);
			this->tab3_TimeSet->Controls->Add(this->textBox8);
			this->tab3_TimeSet->Controls->Add(this->ApplyTimeSet);
			this->tab3_TimeSet->Controls->Add(this->label35);
			this->tab3_TimeSet->Controls->Add(this->textBox6);
			this->tab3_TimeSet->Location = System::Drawing::Point(4, 22);
			this->tab3_TimeSet->Name = L"tab3_TimeSet";
			this->tab3_TimeSet->Padding = System::Windows::Forms::Padding(3);
			this->tab3_TimeSet->Size = System::Drawing::Size(584, 159);
			this->tab3_TimeSet->TabIndex = 2;
			this->tab3_TimeSet->Text = L"Задание продолжительности";
			this->tab3_TimeSet->UseVisualStyleBackColor = true;
			// 
			// tab4_PID
			// 
			this->tab4_PID->Controls->Add(this->ApplyPID);
			this->tab4_PID->Controls->Add(this->label45);
			this->tab4_PID->Controls->Add(this->label44);
			this->tab4_PID->Controls->Add(this->label43);
			this->tab4_PID->Controls->Add(this->label42);
			this->tab4_PID->Controls->Add(this->NCurrent);
			this->tab4_PID->Controls->Add(this->label41);
			this->tab4_PID->Controls->Add(this->label40);
			this->tab4_PID->Controls->Add(this->label39);
			this->tab4_PID->Controls->Add(this->label38);
			this->tab4_PID->Controls->Add(this->label37);
			this->tab4_PID->Controls->Add(this->NSetpoint);
			this->tab4_PID->Controls->Add(this->KdMult);
			this->tab4_PID->Controls->Add(this->KdVal);
			this->tab4_PID->Controls->Add(this->KiMult);
			this->tab4_PID->Controls->Add(this->KiVal);
			this->tab4_PID->Controls->Add(this->KpMult);
			this->tab4_PID->Controls->Add(this->KpVal);
			this->tab4_PID->Controls->Add(this->label36);
			this->tab4_PID->Controls->Add(this->textBox7);
			this->tab4_PID->Location = System::Drawing::Point(4, 22);
			this->tab4_PID->Name = L"tab4_PID";
			this->tab4_PID->Padding = System::Windows::Forms::Padding(3);
			this->tab4_PID->Size = System::Drawing::Size(584, 159);
			this->tab4_PID->TabIndex = 3;
			this->tab4_PID->Text = L"Управление по ПИД";
			this->tab4_PID->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(89, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Текущий режим";
			// 
			// tbCurrentMode
			// 
			this->tbCurrentMode->Enabled = false;
			this->tbCurrentMode->Location = System::Drawing::Point(122, 31);
			this->tbCurrentMode->Name = L"tbCurrentMode";
			this->tbCurrentMode->Size = System::Drawing::Size(100, 20);
			this->tbCurrentMode->TabIndex = 6;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 71);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(149, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Доступные режимы работы";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 41);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(109, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Скорость вращения";
			// 
			// NCurrentProgress
			// 
			this->NCurrentProgress->BackColor = System::Drawing::SystemColors::Control;
			this->NCurrentProgress->Location = System::Drawing::Point(157, 43);
			this->NCurrentProgress->Name = L"NCurrentProgress";
			this->NCurrentProgress->Size = System::Drawing::Size(140, 10);
			this->NCurrentProgress->TabIndex = 1;
			this->NCurrentProgress->Value = 70;
			// 
			// Nmin
			// 
			this->Nmin->Location = System::Drawing::Point(112, 38);
			this->Nmin->Name = L"Nmin";
			this->Nmin->Size = System::Drawing::Size(39, 20);
			this->Nmin->TabIndex = 2;
			// 
			// Nmax
			// 
			this->Nmax->Location = System::Drawing::Point(303, 38);
			this->Nmax->Name = L"Nmax";
			this->Nmax->Size = System::Drawing::Size(39, 20);
			this->Nmax->TabIndex = 3;
			// 
			// NCurrentValue
			// 
			this->NCurrentValue->Enabled = false;
			this->NCurrentValue->Location = System::Drawing::Point(176, 19);
			this->NCurrentValue->Name = L"NCurrentValue";
			this->NCurrentValue->Size = System::Drawing::Size(47, 20);
			this->NCurrentValue->TabIndex = 4;
			// 
			// NFailureCheck
			// 
			this->NFailureCheck->AutoSize = true;
			this->NFailureCheck->Location = System::Drawing::Point(377, 40);
			this->NFailureCheck->Name = L"NFailureCheck";
			this->NFailureCheck->Size = System::Drawing::Size(15, 14);
			this->NFailureCheck->TabIndex = 5;
			this->NFailureCheck->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(116, 22);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(27, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"мин";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(307, 22);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(33, 13);
			this->label5->TabIndex = 7;
			this->label5->Text = L"макс";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(356, 22);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(125, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"Аварийное отключение";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(229, 22);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(50, 13);
			this->label7->TabIndex = 9;
			this->label7->Text = L"(об/мин)";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(229, 72);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(31, 13);
			this->label8->TabIndex = 19;
			this->label8->Text = L"(бар)";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(374, 72);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(35, 13);
			this->label9->TabIndex = 18;
			this->label9->Text = L"label9";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(307, 72);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(33, 13);
			this->label10->TabIndex = 17;
			this->label10->Text = L"макс";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(116, 72);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(27, 13);
			this->label11->TabIndex = 16;
			this->label11->Text = L"мин";
			// 
			// PMFailureCheck
			// 
			this->PMFailureCheck->AutoSize = true;
			this->PMFailureCheck->Location = System::Drawing::Point(377, 90);
			this->PMFailureCheck->Name = L"PMFailureCheck";
			this->PMFailureCheck->Size = System::Drawing::Size(15, 14);
			this->PMFailureCheck->TabIndex = 15;
			this->PMFailureCheck->UseVisualStyleBackColor = true;
			// 
			// PMCurrentValue
			// 
			this->PMCurrentValue->Enabled = false;
			this->PMCurrentValue->Location = System::Drawing::Point(176, 67);
			this->PMCurrentValue->Name = L"PMCurrentValue";
			this->PMCurrentValue->Size = System::Drawing::Size(47, 20);
			this->PMCurrentValue->TabIndex = 14;
			// 
			// PMmax
			// 
			this->PMmax->Location = System::Drawing::Point(303, 88);
			this->PMmax->Name = L"PMmax";
			this->PMmax->Size = System::Drawing::Size(39, 20);
			this->PMmax->TabIndex = 13;
			// 
			// PMmin
			// 
			this->PMmin->Location = System::Drawing::Point(112, 88);
			this->PMmin->Name = L"PMmin";
			this->PMmin->Size = System::Drawing::Size(39, 20);
			this->PMmin->TabIndex = 12;
			// 
			// PMCurrentProgress
			// 
			this->PMCurrentProgress->BackColor = System::Drawing::SystemColors::Control;
			this->PMCurrentProgress->Location = System::Drawing::Point(157, 93);
			this->PMCurrentProgress->Name = L"PMCurrentProgress";
			this->PMCurrentProgress->Size = System::Drawing::Size(140, 10);
			this->PMCurrentProgress->TabIndex = 11;
			this->PMCurrentProgress->Value = 90;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(6, 90);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(93, 13);
			this->label12->TabIndex = 10;
			this->label12->Text = L"Давление масла";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(374, 124);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(41, 13);
			this->label14->TabIndex = 28;
			this->label14->Text = L"label14";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(307, 124);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(33, 13);
			this->label15->TabIndex = 27;
			this->label15->Text = L"макс";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(116, 124);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(27, 13);
			this->label16->TabIndex = 26;
			this->label16->Text = L"мин";
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(377, 142);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(15, 14);
			this->checkBox3->TabIndex = 25;
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// QCCurrentValue
			// 
			this->QCCurrentValue->Enabled = false;
			this->QCCurrentValue->Location = System::Drawing::Point(176, 121);
			this->QCCurrentValue->Name = L"QCCurrentValue";
			this->QCCurrentValue->Size = System::Drawing::Size(47, 20);
			this->QCCurrentValue->TabIndex = 24;
			// 
			// QCmax
			// 
			this->QCmax->Location = System::Drawing::Point(303, 140);
			this->QCmax->Name = L"QCmax";
			this->QCmax->Size = System::Drawing::Size(39, 20);
			this->QCmax->TabIndex = 23;
			// 
			// QCmin
			// 
			this->QCmin->Location = System::Drawing::Point(112, 140);
			this->QCmin->Name = L"QCmin";
			this->QCmin->Size = System::Drawing::Size(39, 20);
			this->QCmin->TabIndex = 22;
			// 
			// QCCurrentProgress
			// 
			this->QCCurrentProgress->BackColor = System::Drawing::SystemColors::Control;
			this->QCCurrentProgress->Location = System::Drawing::Point(157, 145);
			this->QCCurrentProgress->Name = L"QCCurrentProgress";
			this->QCCurrentProgress->Size = System::Drawing::Size(140, 10);
			this->QCCurrentProgress->TabIndex = 21;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(6, 142);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(46, 13);
			this->label17->TabIndex = 20;
			this->label17->Text = L"Впрыск";
			// 
			// numericUpDown7
			// 
			this->numericUpDown7->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->numericUpDown7->Location = System::Drawing::Point(19, 61);
			this->numericUpDown7->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10000, 0, 0, 0});
			this->numericUpDown7->Name = L"numericUpDown7";
			this->numericUpDown7->Size = System::Drawing::Size(75, 20);
			this->numericUpDown7->TabIndex = 0;
			// 
			// numericUpDown8
			// 
			this->numericUpDown8->Location = System::Drawing::Point(140, 61);
			this->numericUpDown8->Name = L"numericUpDown8";
			this->numericUpDown8->Size = System::Drawing::Size(52, 20);
			this->numericUpDown8->TabIndex = 1;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label18->Location = System::Drawing::Point(16, 26);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(128, 13);
			this->label18->TabIndex = 2;
			this->label18->Text = L"Форсирующий импульс";
			this->label18->Click += gcnew System::EventHandler(this, &Form1::label18_Click);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Underline, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(204)));
			this->label19->Location = System::Drawing::Point(16, 101);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(134, 13);
			this->label19->TabIndex = 5;
			this->label19->Text = L"Удерживающий импульс";
			// 
			// numericUpDown9
			// 
			this->numericUpDown9->Location = System::Drawing::Point(140, 135);
			this->numericUpDown9->Name = L"numericUpDown9";
			this->numericUpDown9->Size = System::Drawing::Size(52, 20);
			this->numericUpDown9->TabIndex = 4;
			// 
			// numericUpDown10
			// 
			this->numericUpDown10->Enabled = false;
			this->numericUpDown10->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->numericUpDown10->Location = System::Drawing::Point(19, 135);
			this->numericUpDown10->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {50000, 0, 0, 0});
			this->numericUpDown10->Name = L"numericUpDown10";
			this->numericUpDown10->Size = System::Drawing::Size(75, 20);
			this->numericUpDown10->TabIndex = 3;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(28, 180);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(30, 13);
			this->label20->TabIndex = 8;
			this->label20->Text = L"ВМТ";
			// 
			// numericUpDown11
			// 
			this->numericUpDown11->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 65536});
			this->numericUpDown11->Location = System::Drawing::Point(140, 200);
			this->numericUpDown11->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {360, 0, 0, 0});
			this->numericUpDown11->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {360, 0, 0, System::Int32::MinValue});
			this->numericUpDown11->Name = L"numericUpDown11";
			this->numericUpDown11->Size = System::Drawing::Size(52, 20);
			this->numericUpDown11->TabIndex = 7;
			// 
			// numericUpDown12
			// 
			this->numericUpDown12->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 65536});
			this->numericUpDown12->Location = System::Drawing::Point(19, 200);
			this->numericUpDown12->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {360, 0, 0, 0});
			this->numericUpDown12->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {360, 0, 0, System::Int32::MinValue});
			this->numericUpDown12->Name = L"numericUpDown12";
			this->numericUpDown12->Size = System::Drawing::Size(75, 20);
			this->numericUpDown12->TabIndex = 6;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(129, 171);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(93, 26);
			this->label21->TabIndex = 9;
			this->label21->Text = L"Запаздывание / \r\nопережение";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(100, 63);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(27, 13);
			this->label22->TabIndex = 10;
			this->label22->Text = L"мкс";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(100, 137);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(27, 13);
			this->label23->TabIndex = 11;
			this->label23->Text = L"мкс";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(198, 63);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(15, 13);
			this->label24->TabIndex = 12;
			this->label24->Text = L"%";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(198, 137);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(15, 13);
			this->label25->TabIndex = 13;
			this->label25->Text = L"%";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(16, 45);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(111, 13);
			this->label26->TabIndex = 14;
			this->label26->Text = L"Продолжительность";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Location = System::Drawing::Point(133, 45);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(69, 13);
			this->label30->TabIndex = 15;
			this->label30->Text = L"Скважность";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(133, 119);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(69, 13);
			this->label31->TabIndex = 17;
			this->label31->Text = L"Скважность";
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(16, 119);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(111, 13);
			this->label32->TabIndex = 16;
			this->label32->Text = L"Продолжительность";
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->CheckAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->checkBox4->Enabled = false;
			this->checkBox4->Location = System::Drawing::Point(92, 188);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(42, 31);
			this->checkBox4->TabIndex = 30;
			this->checkBox4->Text = L"Связь";
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->CheckAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->checkBox5->Enabled = false;
			this->checkBox5->Location = System::Drawing::Point(138, 189);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(36, 31);
			this->checkBox5->TabIndex = 31;
			this->checkBox5->Text = L"Холл";
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->CheckAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->checkBox6->Enabled = false;
			this->checkBox6->Location = System::Drawing::Point(173, 189);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(50, 31);
			this->checkBox6->TabIndex = 32;
			this->checkBox6->Text = L"Впрыск";
			this->checkBox6->UseVisualStyleBackColor = true;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(9, 25);
			this->textBox4->Multiline = true;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(223, 128);
			this->textBox4->TabIndex = 0;
			this->textBox4->Text = L"В режиме ожидания блок не осуществляет подачу импульсов на форсунки, однако отсле" 
				L"живает все сигналы датчиков и выводит различную информацию.";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Location = System::Drawing::Point(6, 9);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(128, 13);
			this->label33->TabIndex = 1;
			this->label33->Text = L"Информация о режиме:";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Location = System::Drawing::Point(6, 9);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(128, 13);
			this->label34->TabIndex = 3;
			this->label34->Text = L"Информация о режиме:";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(9, 25);
			this->textBox5->Multiline = true;
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(223, 128);
			this->textBox5->TabIndex = 2;
			this->textBox5->Text = resources->GetString(L"textBox5.Text");
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &Form1::textBox5_TextChanged);
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(6, 9);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(128, 13);
			this->label35->TabIndex = 3;
			this->label35->Text = L"Информация о режиме:";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(9, 25);
			this->textBox6->Multiline = true;
			this->textBox6->Name = L"textBox6";
			this->textBox6->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox6->Size = System::Drawing::Size(223, 128);
			this->textBox6->TabIndex = 2;
			this->textBox6->Text = resources->GetString(L"textBox6.Text");
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(6, 9);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(128, 13);
			this->label36->TabIndex = 3;
			this->label36->Text = L"Информация о режиме:";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(9, 25);
			this->textBox7->Multiline = true;
			this->textBox7->Name = L"textBox7";
			this->textBox7->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox7->Size = System::Drawing::Size(223, 128);
			this->textBox7->TabIndex = 2;
			this->textBox7->Text = resources->GetString(L"textBox7.Text");
			// 
			// KpVal
			// 
			this->KpVal->Location = System::Drawing::Point(477, 24);
			this->KpVal->Name = L"KpVal";
			this->KpVal->Size = System::Drawing::Size(38, 20);
			this->KpVal->TabIndex = 4;
			// 
			// KpMult
			// 
			this->KpMult->Location = System::Drawing::Point(521, 24);
			this->KpMult->Name = L"KpMult";
			this->KpMult->Size = System::Drawing::Size(38, 20);
			this->KpMult->TabIndex = 5;
			// 
			// KiVal
			// 
			this->KiVal->Location = System::Drawing::Point(477, 50);
			this->KiVal->Name = L"KiVal";
			this->KiVal->Size = System::Drawing::Size(38, 20);
			this->KiVal->TabIndex = 6;
			// 
			// KiMult
			// 
			this->KiMult->Location = System::Drawing::Point(521, 50);
			this->KiMult->Name = L"KiMult";
			this->KiMult->Size = System::Drawing::Size(38, 20);
			this->KiMult->TabIndex = 7;
			// 
			// KdVal
			// 
			this->KdVal->Location = System::Drawing::Point(477, 75);
			this->KdVal->Name = L"KdVal";
			this->KdVal->Size = System::Drawing::Size(38, 20);
			this->KdVal->TabIndex = 8;
			// 
			// KdMult
			// 
			this->KdMult->Location = System::Drawing::Point(521, 75);
			this->KdMult->Name = L"KdMult";
			this->KdMult->Size = System::Drawing::Size(38, 20);
			this->KdMult->TabIndex = 9;
			// 
			// NSetpoint
			// 
			this->NSetpoint->Location = System::Drawing::Point(350, 47);
			this->NSetpoint->Name = L"NSetpoint";
			this->NSetpoint->Size = System::Drawing::Size(38, 20);
			this->NSetpoint->TabIndex = 10;
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Location = System::Drawing::Point(250, 52);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(94, 13);
			this->label37->TabIndex = 11;
			this->label37->Text = L"Уставка частоты";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(448, 27);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(20, 13);
			this->label38->TabIndex = 12;
			this->label38->Text = L"Кп";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(448, 53);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(20, 13);
			this->label39->TabIndex = 13;
			this->label39->Text = L"Ки";
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(448, 78);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(20, 13);
			this->label40->TabIndex = 14;
			this->label40->Text = L"Кд";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(394, 50);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(44, 13);
			this->label41->TabIndex = 15;
			this->label41->Text = L"об/мин";
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(250, 27);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(94, 13);
			this->label42->TabIndex = 17;
			this->label42->Text = L"Текущая частота";
			// 
			// NCurrent
			// 
			this->NCurrent->Enabled = false;
			this->NCurrent->Location = System::Drawing::Point(350, 22);
			this->NCurrent->Name = L"NCurrent";
			this->NCurrent->Size = System::Drawing::Size(38, 20);
			this->NCurrent->TabIndex = 16;
			// 
			// label43
			// 
			this->label43->AutoSize = true;
			this->label43->Location = System::Drawing::Point(394, 25);
			this->label43->Name = L"label43";
			this->label43->Size = System::Drawing::Size(44, 13);
			this->label43->TabIndex = 18;
			this->label43->Text = L"об/мин";
			// 
			// label44
			// 
			this->label44->AutoSize = true;
			this->label44->Location = System::Drawing::Point(479, 8);
			this->label44->Name = L"label44";
			this->label44->Size = System::Drawing::Size(36, 13);
			this->label44->TabIndex = 19;
			this->label44->Text = L"число";
			// 
			// label45
			// 
			this->label45->AutoSize = true;
			this->label45->Location = System::Drawing::Point(512, 8);
			this->label45->Name = L"label45";
			this->label45->Size = System::Drawing::Size(64, 13);
			this->label45->TabIndex = 20;
			this->label45->Text = L"множитель";
			// 
			// ApplyTimeSet
			// 
			this->ApplyTimeSet->Location = System::Drawing::Point(259, 128);
			this->ApplyTimeSet->Name = L"ApplyTimeSet";
			this->ApplyTimeSet->Size = System::Drawing::Size(86, 25);
			this->ApplyTimeSet->TabIndex = 4;
			this->ApplyTimeSet->Text = L"Применить";
			this->ApplyTimeSet->UseVisualStyleBackColor = true;
			// 
			// ApplyPeriodic
			// 
			this->ApplyPeriodic->Location = System::Drawing::Point(259, 128);
			this->ApplyPeriodic->Name = L"ApplyPeriodic";
			this->ApplyPeriodic->Size = System::Drawing::Size(86, 25);
			this->ApplyPeriodic->TabIndex = 4;
			this->ApplyPeriodic->Text = L"Применить";
			this->ApplyPeriodic->UseVisualStyleBackColor = true;
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(259, 38);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(62, 20);
			this->textBox8->TabIndex = 6;
			// 
			// label46
			// 
			this->label46->AutoSize = true;
			this->label46->Location = System::Drawing::Point(256, 22);
			this->label46->Name = L"label46";
			this->label46->Size = System::Drawing::Size(158, 13);
			this->label46->TabIndex = 7;
			this->label46->Text = L"Продолжительность впрыска";
			// 
			// label47
			// 
			this->label47->AutoSize = true;
			this->label47->Location = System::Drawing::Point(256, 22);
			this->label47->Name = L"label47";
			this->label47->Size = System::Drawing::Size(158, 13);
			this->label47->TabIndex = 10;
			this->label47->Text = L"Продолжительность впрыска";
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(259, 38);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(62, 20);
			this->textBox9->TabIndex = 9;
			// 
			// label48
			// 
			this->label48->AutoSize = true;
			this->label48->Location = System::Drawing::Point(256, 73);
			this->label48->Name = L"label48";
			this->label48->Size = System::Drawing::Size(132, 13);
			this->label48->TabIndex = 13;
			this->label48->Text = L"Периодичность впрыска";
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(259, 89);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(62, 20);
			this->textBox10->TabIndex = 12;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(6, 206);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(70, 13);
			this->label13->TabIndex = 34;
			this->label13->Text = L"Индикаторы";
			// 
			// label49
			// 
			this->label49->AutoSize = true;
			this->label49->Location = System::Drawing::Point(100, 203);
			this->label49->Name = L"label49";
			this->label49->Size = System::Drawing::Size(33, 13);
			this->label49->TabIndex = 18;
			this->label49->Text = L"град.";
			// 
			// label50
			// 
			this->label50->AutoSize = true;
			this->label50->Location = System::Drawing::Point(198, 203);
			this->label50->Name = L"label50";
			this->label50->Size = System::Drawing::Size(33, 13);
			this->label50->TabIndex = 19;
			this->label50->Text = L"град.";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"(мкс)", L"(градусы)", L"(г/цикл)"});
			this->comboBox1->Location = System::Drawing::Point(338, 38);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(75, 21);
			this->comboBox1->TabIndex = 14;
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"(мкс)", L"(градусы)", L"(г/цикл)"});
			this->comboBox2->Location = System::Drawing::Point(232, 121);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(65, 21);
			this->comboBox2->TabIndex = 15;
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"(сек)", L"(мс)", L"(мкс)"});
			this->comboBox3->Location = System::Drawing::Point(337, 88);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(77, 21);
			this->comboBox3->TabIndex = 16;
			// 
			// comboBox4
			// 
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"(мкс)", L"(градусы)", L"(г/цикл)"});
			this->comboBox4->Location = System::Drawing::Point(327, 38);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(77, 21);
			this->comboBox4->TabIndex = 17;
			// 
			// listView1
			// 
			this->listView1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(3) {listViewItem1, listViewItem2, 
				listViewItem3});
			this->listView1->Location = System::Drawing::Point(346, 82);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(102, 27);
			this->listView1->TabIndex = 18;
			this->listView1->UseCompatibleStateImageBehavior = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(1175, 521);
			this->Controls->Add(this->logCheck);
			this->Controls->Add(this->logFileName);
			this->Controls->Add(this->writeLogButton);
			this->Controls->Add(this->sendButton);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->initButton);
			this->Controls->Add(this->textId1);
			this->Controls->Add(this->buttonRandIn);
			this->Controls->Add(this->buttonRandOut);
			this->Controls->Add(this->textRandIn);
			this->Controls->Add(this->textRandOut);
			this->Controls->Add(this->textId2);
			this->Controls->Add(this->label27);
			this->Controls->Add(this->label28);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::form1_FormClosing);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bindingSource1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->canParametersDataSet))->EndInit();
			this->tabParameters->ResumeLayout(false);
			this->tabParameters->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ParametersDataGrid))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabControlPage->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->tctrlModeParameters->ResumeLayout(false);
			this->tab1_Standby->ResumeLayout(false);
			this->tab1_Standby->PerformLayout();
			this->tab2_Period->ResumeLayout(false);
			this->tab2_Period->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tab3_TimeSet->ResumeLayout(false);
			this->tab3_TimeSet->PerformLayout();
			this->tab4_PID->ResumeLayout(false);
			this->tab4_PID->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Nmin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Nmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PMmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PMmin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->QCmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->QCmin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown12))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	public: System::Void form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);

	void can_init(void);
	BOOL m_fIsInitialized;
	public: //long int nMessage;
			bool isLogWrite;

	 //[SecurityPermission(SecurityAction::Demand, Flags=SecurityPermissionFlag::UnmanagedCode)]
      protected: virtual void WndProc( Message% m ) override
	 {
		// Listen for operating system messages.
		switch ( m.Msg )
        {
		case WM_UCAN_RECEIVE:
			onCanRecieve();
			break;
         }
         Form::WndProc( m );
     }

	 void onCanRecieve(); 
	 BOOL readMsg(tCanMsgStruct* pCanMsg_p);
	 void printMsg(tCanMsgStruct *pCanMsg_p);

	 void onVmtSearch(); 
	 void onCanTransmit(); 
	 BOOL writeMsg(tCanMsgStruct* pCanMsg_p);
	 void canWrite(int id1, int id2, int id3, float a);
	 void canWrite(int id1, int id2, int id3, int a);
	 
private: System::Void sendButton_Click(System::Object^  sender, System::EventArgs^  e);

	public: CC_VEngine* eng;



private: System::Void buttonRandIn_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void buttonRandOut_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void writeLogButton_Click(System::Object^  sender, System::EventArgs^  e) {
			
			if (!isLogWrite)
			{
				clearFile(&(SysToStd(logFileName->Text+".txt")));
				nMessage = 0;
			} else {
				// сохраняем в лог то, что есть
				flushToFile(&(SysToStd(logFileName->Text+".txt")));
			}
			isLogWrite = !isLogWrite;
			logCheck->Checked = isLogWrite;
		 }
private: System::Void initButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 // инициализировать
			 /*this->checkmanQCOut->Checked = this->checkmanQCIn->Checked;
			 this->checkmanAngleOut->Checked = this->checkmanAngleIn->Checked;
			 this->textQCAnOut->Text = this->textQCAnIn->Text;
			 this->checkmanInjOut->Checked = this->checkmanInjIn->Checked;
			 this->checkinjOnceOut->Checked = this->checkinjOnceIn->Checked;
			 this->textmanNOut->Text = this->textmanNIn->Text;
			 this->checkManModeOut->Checked = this->checkManModeIn->Checked;
			 this->checkmanPedOut->Checked = this->checkmanPedIn->Checked;
			 this->checkManLedOut->Checked = this->checkManLedIn->Checked;
			 this->checkCanSendOut->Checked = this->checkCanSendIn->Checked;
			 this->checkCanTimeOut->Checked = this->checkCanTimeIn->Checked;
			 this->checkmanUOVTOut->Checked = this->checkmanUOVTIn->Checked;
			 this->textinjUOVTOut->Text = this->textinjUOVTIn->Text;
			 this->comboModeOut->SelectedIndex = this->comboMode->SelectedIndex;
			 this->textnUOut->Text = this->textnUIn->Text;
			 this->textInjD1Out->Text = this->textInjD1In->Text;
			 this->textInjD2Out->Text = this->textInjD2In->Text;
			 this->textInjT1Out->Text = this->textInjT1In->Text;
			 this->textInjT2Out->Text = this->textInjT2In->Text;
			 this->textQCtOut->Text = this->textQCtIn->Text;
			 this->checkManQCtOut->Checked = this->checkManQCtIn->Checked;
			 this->checkManFdbkOut->Checked = this->checkManFdbkIn->Checked;
			 this->numVMTOut->Value = Decimal::Parse(this->textVMTIn->Text);

			 this->KpValOut->Text = this->KpValIn->Text;
			 this->KiValOut->Text = this->KiValIn->Text;
			 this->KdValOut->Text = this->KdValIn->Text;
			 this->KpMultOut->Text = this->KpMultIn->Text;
			 this->KiMultOut->Text = this->KiMultIn->Text;
			 this->KdMultOut->Text = this->KdMultIn->Text;
			 */
		 }
private: System::Void checkmanUOVTIn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void checkmanUOVTOut_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void numVMTOut_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 onVmtSearch();
		 }
private: System::Void label29_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void ParametersDataGrid_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
			 if ((e->RowIndex >= ParametersDataGrid->NewRowIndex) || (e->RowIndex <= 0))
				 return;
			 
			 int idp;
			 System::Globalization::CultureInfo^ provider = System::Globalization::CultureInfo::InvariantCulture;

			 String^ tmp = (String^)ParametersDataGrid->Rows[e->RowIndex]->Cells[2]->Value;
			 tmp = tmp->Replace("0x","");
			 if (Int32::TryParse(tmp, System::Globalization::NumberStyles::HexNumber, provider, idp))
			 {
				 this->textId1->Text = "" + idp;
			 }
			 else
			 {
				 this->textId2->Text = "0";
			 }
			 
			 int ids1;
			 tmp = (String^)ParametersDataGrid->Rows[e->RowIndex]->Cells[3]->Value;
			 tmp->Replace("0x","");
			 if (Int32::TryParse(tmp, System::Globalization::NumberStyles::HexNumber, provider, ids1))
			 {
				 this->textId2->Text = "" + ids1;
			 }
			 else
			 {
				 this->textId2->Text = "0";
			 }
		 }
private: System::Void label29_Click_1(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 ParametersDataGrid->CurrentCell = nullptr;
			 for (int i = 0; i < ParametersDataGrid->Rows->Count - 1; i++)
			 {
				 ParametersDataGrid->Rows[i]->Visible = ParametersDataGrid[0, i]->Value->ToString()->ToLower()->Contains(FilterTextBox->Text->ToString()->ToLower())
					 || ParametersDataGrid[1, i]->Value->ToString()->ToLower()->Contains(FilterTextBox->Text->ToString()->ToLower())
					 || ParametersDataGrid[2, i]->Value->ToString()->ToLower()->Contains(FilterTextBox->Text->ToString()->ToLower()); 
			 }
		 }
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label18_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label33_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox5_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}