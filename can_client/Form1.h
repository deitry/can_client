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
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textQCAn;



	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  UOVT;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  Tvprysk;
	private: System::Windows::Forms::Label^  label4;

	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::TextBox^  RPM;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;


	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  valTextBox;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  sendButton;

	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::Label^  label12;

	private: System::Windows::Forms::TextBox^  textBox11;
	private: System::Windows::Forms::CheckBox^  checkManModeIn;

	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::CheckBox^  checkmanAngleOut;

	private: System::Windows::Forms::CheckBox^  checkmanQCOut;
	private: System::Windows::Forms::CheckBox^  checkmanUOVTOut;


	private: System::Windows::Forms::CheckBox^  checkmanUOVTIn;
	private: System::Windows::Forms::CheckBox^  checkCanSendOut;
	private: System::Windows::Forms::CheckBox^  checkmanPedOut;



	private: System::Windows::Forms::CheckBox^  checkinjOnceOut;

	private: System::Windows::Forms::CheckBox^  checkmanInjOut;
	private: System::Windows::Forms::CheckBox^  checkCanSendIn;
	private: System::Windows::Forms::CheckBox^  checkmanPedIn;



	private: System::Windows::Forms::CheckBox^  checkinjOnceIn;

	private: System::Windows::Forms::CheckBox^  checkmanInjIn;

	private: System::Windows::Forms::CheckBox^  checkmanAngleIn;
	private: System::Windows::Forms::CheckBox^  checkmanQCIn;


	private: System::Windows::Forms::CheckBox^  checkManModeOut;
	private: System::Windows::Forms::TextBox^  textInjD2In;


	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::TextBox^  textInjD1In;


	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::TextBox^  textInjT2In;

	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textInjT1In;

	private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::TextBox^  textInjD2Out;

private: System::Windows::Forms::TextBox^  textInjD1Out;
private: System::Windows::Forms::TextBox^  textInjT2Out;
private: System::Windows::Forms::TextBox^  textInjT1Out;
private: System::Windows::Forms::TextBox^  textnUIn;
private: System::Windows::Forms::TextBox^  textnUOut;
private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::TextBox^  textQCtOut;

private: System::Windows::Forms::TextBox^  textQCtIn;
private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::TextBox^  textQCAnOut;
private: System::Windows::Forms::TextBox^  textQCAnIn;
private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::TextBox^  textinjUOVTOut;

private: System::Windows::Forms::TextBox^  textinjUOVTIn;

private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::TextBox^  textmanNOut;
private: System::Windows::Forms::TextBox^  textmanNIn;
private: System::Windows::Forms::ComboBox^  comboMode;
private: System::Windows::Forms::ComboBox^  comboModeOut;
private: System::Windows::Forms::CheckBox^  checkManFdbkOut;

private: System::Windows::Forms::CheckBox^  checkManFdbkIn;

private: System::Windows::Forms::TextBox^  textProgTime;
private: System::Windows::Forms::DataGridView^  gridFdbk;

private: System::Windows::Forms::TextBox^  textId2;
private: System::Windows::Forms::TextBox^  textId1;
private: System::Windows::Forms::TextBox^  textRandOut;
private: System::Windows::Forms::TextBox^  textRandIn;

private: System::Windows::Forms::Button^  buttonRandOut;
private: System::Windows::Forms::Button^  buttonRandIn;

private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column6;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column7;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column8;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column9;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column10;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column11;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column12;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column13;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column14;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column15;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column16;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column17;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column18;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column19;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column20;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column21;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column22;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column23;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column24;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column25;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column26;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column27;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column28;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column29;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column30;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column31;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column32;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column33;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column34;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column35;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column36;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column37;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column38;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column39;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column40;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column41;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column42;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column43;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column44;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column45;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column46;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column47;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column48;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column49;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column50;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column51;
private: System::Windows::Forms::Button^  writeLogButton;
private: System::Windows::Forms::TextBox^  logFileName;
private: System::Windows::Forms::CheckBox^  logCheck;
private: System::Windows::Forms::CheckBox^  checkManQCtIn;
private: System::Windows::Forms::CheckBox^  checkManQCtOut;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::NumericUpDown^  numVMTOut;
private: System::Windows::Forms::TextBox^  textVMTIn;
private: System::Windows::Forms::TextBox^  dT_ms;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::Label^  label25;
private: System::Windows::Forms::Label^  label24;
private: System::Windows::Forms::TextBox^  textIntTime1;

private: System::Windows::Forms::TextBox^  textIntTime;
private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::Label^  label27;
private: System::Windows::Forms::CheckBox^  checkCanTimeOut;
private: System::Windows::Forms::CheckBox^  checkCanTimeIn;
private: System::Windows::Forms::CheckBox^  checkManLedOut;

private: System::Windows::Forms::CheckBox^  checkManLedIn;
private: System::Windows::Forms::Label^  label31;
private: System::Windows::Forms::Label^  kI;

private: System::Windows::Forms::Label^  kP;
private: System::Windows::Forms::TextBox^  KdMultOut;


private: System::Windows::Forms::TextBox^  KdValOut;

private: System::Windows::Forms::TextBox^  KiMultOut;


private: System::Windows::Forms::TextBox^  KiValOut;

private: System::Windows::Forms::TextBox^  KpMultOut;


private: System::Windows::Forms::TextBox^  KpValOut;

private: System::Windows::Forms::TextBox^  KpValIn;
private: System::Windows::Forms::TextBox^  KdMultIn;

private: System::Windows::Forms::TextBox^  KdValIn;

private: System::Windows::Forms::TextBox^  KiMultIn;

private: System::Windows::Forms::TextBox^  KiValIn;

private: System::Windows::Forms::TextBox^  KpMultIn;
private: System::Windows::Forms::TabPage^  tabPage4;
private: System::Windows::Forms::DataGridView^  ParametersDataGrid;
private: System::Data::DataSet^  canParametersDataSet;
private: System::Windows::Forms::TextBox^  FilterTextBox;

private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::BindingSource^  bindingSource1;

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
			this->initButton = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->KdMultIn = (gcnew System::Windows::Forms::TextBox());
			this->KdValIn = (gcnew System::Windows::Forms::TextBox());
			this->KiMultIn = (gcnew System::Windows::Forms::TextBox());
			this->KiValIn = (gcnew System::Windows::Forms::TextBox());
			this->KpMultIn = (gcnew System::Windows::Forms::TextBox());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->kI = (gcnew System::Windows::Forms::Label());
			this->kP = (gcnew System::Windows::Forms::Label());
			this->KdMultOut = (gcnew System::Windows::Forms::TextBox());
			this->KdValOut = (gcnew System::Windows::Forms::TextBox());
			this->KiMultOut = (gcnew System::Windows::Forms::TextBox());
			this->KiValOut = (gcnew System::Windows::Forms::TextBox());
			this->KpMultOut = (gcnew System::Windows::Forms::TextBox());
			this->KpValOut = (gcnew System::Windows::Forms::TextBox());
			this->KpValIn = (gcnew System::Windows::Forms::TextBox());
			this->textVMTIn = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->numVMTOut = (gcnew System::Windows::Forms::NumericUpDown());
			this->comboModeOut = (gcnew System::Windows::Forms::ComboBox());
			this->comboMode = (gcnew System::Windows::Forms::ComboBox());
			this->textnUIn = (gcnew System::Windows::Forms::TextBox());
			this->textnUOut = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->valTextBox = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textQCAn = (gcnew System::Windows::Forms::TextBox());
			this->UOVT = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->Tvprysk = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->RPM = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->checkManLedOut = (gcnew System::Windows::Forms::CheckBox());
			this->checkManLedIn = (gcnew System::Windows::Forms::CheckBox());
			this->checkCanTimeOut = (gcnew System::Windows::Forms::CheckBox());
			this->checkCanTimeIn = (gcnew System::Windows::Forms::CheckBox());
			this->dT_ms = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->textIntTime1 = (gcnew System::Windows::Forms::TextBox());
			this->textIntTime = (gcnew System::Windows::Forms::TextBox());
			this->checkManQCtIn = (gcnew System::Windows::Forms::CheckBox());
			this->checkManQCtOut = (gcnew System::Windows::Forms::CheckBox());
			this->gridFdbk = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column11 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column12 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column13 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column14 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column15 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column16 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column17 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column18 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column19 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column20 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column21 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column22 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column23 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column24 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column25 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column26 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column27 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column28 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column29 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column30 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column31 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column32 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column33 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column34 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column35 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column36 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column37 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column38 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column39 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column40 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column41 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column42 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column43 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column44 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column45 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column46 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column47 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column48 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column49 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column50 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column51 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->textProgTime = (gcnew System::Windows::Forms::TextBox());
			this->checkManFdbkOut = (gcnew System::Windows::Forms::CheckBox());
			this->checkManFdbkIn = (gcnew System::Windows::Forms::CheckBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->textinjUOVTOut = (gcnew System::Windows::Forms::TextBox());
			this->textinjUOVTIn = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->textmanNOut = (gcnew System::Windows::Forms::TextBox());
			this->textmanNIn = (gcnew System::Windows::Forms::TextBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->textQCAnOut = (gcnew System::Windows::Forms::TextBox());
			this->textQCAnIn = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textQCtOut = (gcnew System::Windows::Forms::TextBox());
			this->textQCtIn = (gcnew System::Windows::Forms::TextBox());
			this->checkManModeOut = (gcnew System::Windows::Forms::CheckBox());
			this->checkmanUOVTOut = (gcnew System::Windows::Forms::CheckBox());
			this->checkmanUOVTIn = (gcnew System::Windows::Forms::CheckBox());
			this->checkCanSendOut = (gcnew System::Windows::Forms::CheckBox());
			this->checkmanPedOut = (gcnew System::Windows::Forms::CheckBox());
			this->checkinjOnceOut = (gcnew System::Windows::Forms::CheckBox());
			this->checkmanInjOut = (gcnew System::Windows::Forms::CheckBox());
			this->checkCanSendIn = (gcnew System::Windows::Forms::CheckBox());
			this->checkmanPedIn = (gcnew System::Windows::Forms::CheckBox());
			this->checkinjOnceIn = (gcnew System::Windows::Forms::CheckBox());
			this->checkmanInjIn = (gcnew System::Windows::Forms::CheckBox());
			this->checkmanAngleIn = (gcnew System::Windows::Forms::CheckBox());
			this->checkmanQCIn = (gcnew System::Windows::Forms::CheckBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->checkManModeIn = (gcnew System::Windows::Forms::CheckBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->checkmanAngleOut = (gcnew System::Windows::Forms::CheckBox());
			this->checkmanQCOut = (gcnew System::Windows::Forms::CheckBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->textInjD2Out = (gcnew System::Windows::Forms::TextBox());
			this->textInjD1Out = (gcnew System::Windows::Forms::TextBox());
			this->textInjT2Out = (gcnew System::Windows::Forms::TextBox());
			this->textInjT1Out = (gcnew System::Windows::Forms::TextBox());
			this->textInjD2In = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textInjD1In = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textInjT2In = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textInjT1In = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->ParametersDataGrid = (gcnew System::Windows::Forms::DataGridView());
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
			this->FilterTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numVMTOut))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridFdbk))->BeginInit();
			this->tabPage3->SuspendLayout();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ParametersDataGrid))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bindingSource1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->canParametersDataSet))->BeginInit();
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
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Location = System::Drawing::Point(216, 7);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(955, 664);
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->KdMultIn);
			this->tabPage1->Controls->Add(this->KdValIn);
			this->tabPage1->Controls->Add(this->KiMultIn);
			this->tabPage1->Controls->Add(this->KiValIn);
			this->tabPage1->Controls->Add(this->KpMultIn);
			this->tabPage1->Controls->Add(this->label31);
			this->tabPage1->Controls->Add(this->kI);
			this->tabPage1->Controls->Add(this->kP);
			this->tabPage1->Controls->Add(this->KdMultOut);
			this->tabPage1->Controls->Add(this->KdValOut);
			this->tabPage1->Controls->Add(this->KiMultOut);
			this->tabPage1->Controls->Add(this->KiValOut);
			this->tabPage1->Controls->Add(this->KpMultOut);
			this->tabPage1->Controls->Add(this->KpValOut);
			this->tabPage1->Controls->Add(this->KpValIn);
			this->tabPage1->Controls->Add(this->textVMTIn);
			this->tabPage1->Controls->Add(this->label23);
			this->tabPage1->Controls->Add(this->numVMTOut);
			this->tabPage1->Controls->Add(this->comboModeOut);
			this->tabPage1->Controls->Add(this->comboMode);
			this->tabPage1->Controls->Add(this->textnUIn);
			this->tabPage1->Controls->Add(this->textnUOut);
			this->tabPage1->Controls->Add(this->label18);
			this->tabPage1->Controls->Add(this->textBox10);
			this->tabPage1->Controls->Add(this->textBox9);
			this->tabPage1->Controls->Add(this->textBox8);
			this->tabPage1->Controls->Add(this->textBox7);
			this->tabPage1->Controls->Add(this->textBox6);
			this->tabPage1->Controls->Add(this->textBox5);
			this->tabPage1->Controls->Add(this->textBox4);
			this->tabPage1->Controls->Add(this->textBox3);
			this->tabPage1->Controls->Add(this->label11);
			this->tabPage1->Controls->Add(this->label10);
			this->tabPage1->Controls->Add(this->valTextBox);
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Controls->Add(this->label9);
			this->tabPage1->Controls->Add(this->label8);
			this->tabPage1->Controls->Add(this->label7);
			this->tabPage1->Controls->Add(this->textQCAn);
			this->tabPage1->Controls->Add(this->UOVT);
			this->tabPage1->Controls->Add(this->label6);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->Tvprysk);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->RPM);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(947, 638);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"\"Панель приборов\"";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// KdMultIn
			// 
			this->KdMultIn->Location = System::Drawing::Point(822, 327);
			this->KdMultIn->Name = L"KdMultIn";
			this->KdMultIn->Size = System::Drawing::Size(60, 20);
			this->KdMultIn->TabIndex = 61;
			// 
			// KdValIn
			// 
			this->KdValIn->Location = System::Drawing::Point(764, 327);
			this->KdValIn->Name = L"KdValIn";
			this->KdValIn->Size = System::Drawing::Size(52, 20);
			this->KdValIn->TabIndex = 60;
			// 
			// KiMultIn
			// 
			this->KiMultIn->Location = System::Drawing::Point(698, 326);
			this->KiMultIn->Name = L"KiMultIn";
			this->KiMultIn->Size = System::Drawing::Size(60, 20);
			this->KiMultIn->TabIndex = 59;
			// 
			// KiValIn
			// 
			this->KiValIn->Location = System::Drawing::Point(640, 326);
			this->KiValIn->Name = L"KiValIn";
			this->KiValIn->Size = System::Drawing::Size(52, 20);
			this->KiValIn->TabIndex = 58;
			// 
			// KpMultIn
			// 
			this->KpMultIn->Location = System::Drawing::Point(574, 326);
			this->KpMultIn->Name = L"KpMultIn";
			this->KpMultIn->Size = System::Drawing::Size(60, 20);
			this->KpMultIn->TabIndex = 57;
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(761, 307);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(21, 13);
			this->label31->TabIndex = 56;
			this->label31->Text = L"kD";
			// 
			// kI
			// 
			this->kI->AutoSize = true;
			this->kI->Location = System::Drawing::Point(637, 307);
			this->kI->Name = L"kI";
			this->kI->Size = System::Drawing::Size(16, 13);
			this->kI->TabIndex = 55;
			this->kI->Text = L"kI";
			// 
			// kP
			// 
			this->kP->AutoSize = true;
			this->kP->Location = System::Drawing::Point(519, 307);
			this->kP->Name = L"kP";
			this->kP->Size = System::Drawing::Size(20, 13);
			this->kP->TabIndex = 54;
			this->kP->Text = L"kP";
			this->kP->Click += gcnew System::EventHandler(this, &Form1::label29_Click);
			// 
			// KdMultOut
			// 
			this->KdMultOut->Location = System::Drawing::Point(822, 353);
			this->KdMultOut->Name = L"KdMultOut";
			this->KdMultOut->Size = System::Drawing::Size(60, 20);
			this->KdMultOut->TabIndex = 53;
			this->KdMultOut->Text = L"1e-06";
			// 
			// KdValOut
			// 
			this->KdValOut->Location = System::Drawing::Point(764, 353);
			this->KdValOut->Name = L"KdValOut";
			this->KdValOut->Size = System::Drawing::Size(52, 20);
			this->KdValOut->TabIndex = 52;
			// 
			// KiMultOut
			// 
			this->KiMultOut->Location = System::Drawing::Point(698, 353);
			this->KiMultOut->Name = L"KiMultOut";
			this->KiMultOut->Size = System::Drawing::Size(60, 20);
			this->KiMultOut->TabIndex = 50;
			this->KiMultOut->Text = L"1e-06";
			// 
			// KiValOut
			// 
			this->KiValOut->Location = System::Drawing::Point(640, 353);
			this->KiValOut->Name = L"KiValOut";
			this->KiValOut->Size = System::Drawing::Size(52, 20);
			this->KiValOut->TabIndex = 49;
			// 
			// KpMultOut
			// 
			this->KpMultOut->Location = System::Drawing::Point(574, 353);
			this->KpMultOut->Name = L"KpMultOut";
			this->KpMultOut->Size = System::Drawing::Size(60, 20);
			this->KpMultOut->TabIndex = 47;
			this->KpMultOut->Text = L"1e-06";
			// 
			// KpValOut
			// 
			this->KpValOut->Location = System::Drawing::Point(516, 353);
			this->KpValOut->Name = L"KpValOut";
			this->KpValOut->Size = System::Drawing::Size(52, 20);
			this->KpValOut->TabIndex = 46;
			// 
			// KpValIn
			// 
			this->KpValIn->Location = System::Drawing::Point(516, 326);
			this->KpValIn->Name = L"KpValIn";
			this->KpValIn->Size = System::Drawing::Size(52, 20);
			this->KpValIn->TabIndex = 45;
			// 
			// textVMTIn
			// 
			this->textVMTIn->Location = System::Drawing::Point(23, 270);
			this->textVMTIn->Name = L"textVMTIn";
			this->textVMTIn->Size = System::Drawing::Size(100, 20);
			this->textVMTIn->TabIndex = 42;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(235, 272);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(30, 13);
			this->label23->TabIndex = 41;
			this->label23->Text = L"ВМТ";
			// 
			// numVMTOut
			// 
			this->numVMTOut->DecimalPlaces = 1;
			this->numVMTOut->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 65536});
			this->numVMTOut->Location = System::Drawing::Point(129, 270);
			this->numVMTOut->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {360, 0, 0, 0});
			this->numVMTOut->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {360, 0, 0, System::Int32::MinValue});
			this->numVMTOut->Name = L"numVMTOut";
			this->numVMTOut->Size = System::Drawing::Size(103, 20);
			this->numVMTOut->TabIndex = 40;
			this->numVMTOut->ValueChanged += gcnew System::EventHandler(this, &Form1::numVMTOut_ValueChanged);
			// 
			// comboModeOut
			// 
			this->comboModeOut->DisplayMember = L"1";
			this->comboModeOut->FormattingEnabled = true;
			this->comboModeOut->Items->AddRange(gcnew cli::array< System::Object^  >(12) {L"\"Старт\";", L"\"Холостой ход\";", L"\"Стабилизация частоты\";", 
				L"\"Задание подачи\";", L"\"Экономичность\";", L"\"Максимальная динамика\";", L"\"Останов\";", L"\"Неполадка\";", L"\"Авария\";", 
				L"\"Завершение работы\";", L"\"Неопознанный режим\";", L"\t\t\t\t"});
			this->comboModeOut->Location = System::Drawing::Point(364, 52);
			this->comboModeOut->Name = L"comboModeOut";
			this->comboModeOut->Size = System::Drawing::Size(181, 21);
			this->comboModeOut->TabIndex = 31;
			// 
			// comboMode
			// 
			this->comboMode->DisplayMember = L"1";
			this->comboMode->FormattingEnabled = true;
			this->comboMode->Items->AddRange(gcnew cli::array< System::Object^  >(12) {L"\"Старт\";", L"\"Холостой ход\";", L"\"Стабилизация частоты\";", 
				L"\"Задание подачи\";", L"\"Экономичность\";", L"\"Максимальная динамика\";", L"\"Останов\";", L"\"Неполадка\";", L"\"Авария\";", 
				L"\"Завершение работы\";", L"\"Неопознанный режим\";", L"\t\t\t\t"});
			this->comboMode->Location = System::Drawing::Point(48, 52);
			this->comboMode->Name = L"comboMode";
			this->comboMode->Size = System::Drawing::Size(181, 21);
			this->comboMode->TabIndex = 30;
			// 
			// textnUIn
			// 
			this->textnUIn->Location = System::Drawing::Point(23, 128);
			this->textnUIn->Name = L"textnUIn";
			this->textnUIn->Size = System::Drawing::Size(100, 20);
			this->textnUIn->TabIndex = 29;
			// 
			// textnUOut
			// 
			this->textnUOut->Location = System::Drawing::Point(129, 128);
			this->textnUOut->Name = L"textnUOut";
			this->textnUOut->Size = System::Drawing::Size(100, 20);
			this->textnUOut->TabIndex = 28;
			this->textnUOut->Text = L"0";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(235, 135);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(93, 13);
			this->label18->TabIndex = 27;
			this->label18->Text = L"Уставка, об/мин";
			// 
			// textBox10
			// 
			this->textBox10->Location = System::Drawing::Point(304, 472);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(27, 20);
			this->textBox10->TabIndex = 25;
			// 
			// textBox9
			// 
			this->textBox9->Location = System::Drawing::Point(271, 472);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(27, 20);
			this->textBox9->TabIndex = 24;
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(238, 472);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(27, 20);
			this->textBox8->TabIndex = 23;
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(205, 472);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(27, 20);
			this->textBox7->TabIndex = 22;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(172, 472);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(27, 20);
			this->textBox6->TabIndex = 21;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(137, 472);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(27, 20);
			this->textBox5->TabIndex = 20;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(104, 472);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(27, 20);
			this->textBox4->TabIndex = 19;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(71, 472);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(27, 20);
			this->textBox3->TabIndex = 18;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(561, 438);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(55, 13);
			this->label11->TabIndex = 17;
			this->label11->Text = L"Значение";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(151, 421);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(48, 13);
			this->label10->TabIndex = 16;
			this->label10->Text = L"Данные";
			// 
			// valTextBox
			// 
			this->valTextBox->Location = System::Drawing::Point(522, 472);
			this->valTextBox->Name = L"valTextBox";
			this->valTextBox->Size = System::Drawing::Size(236, 20);
			this->valTextBox->TabIndex = 15;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(615, 91);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 13;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(721, 98);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(135, 13);
			this->label9->TabIndex = 12;
			this->label9->Text = L"Цикловая подача, г/цикл\r\n";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(612, 17);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(127, 13);
			this->label8->TabIndex = 11;
			this->label8->Text = L"Вычисленные значения";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(47, 17);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(159, 13);
			this->label7->TabIndex = 10;
			this->label7->Text = L"Полученные по CAN значения";
			// 
			// textQCAn
			// 
			this->textQCAn->Location = System::Drawing::Point(615, 53);
			this->textQCAn->Name = L"textQCAn";
			this->textQCAn->Size = System::Drawing::Size(100, 20);
			this->textQCAn->TabIndex = 3;
			// 
			// UOVT
			// 
			this->UOVT->Location = System::Drawing::Point(129, 238);
			this->UOVT->Name = L"UOVT";
			this->UOVT->Size = System::Drawing::Size(100, 20);
			this->UOVT->TabIndex = 9;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(721, 60);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(240, 13);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Продолжительность впрыска в градусах ПКВ";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(235, 240);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(37, 13);
			this->label5->TabIndex = 8;
			this->label5->Text = L"УОВТ";
			// 
			// Tvprysk
			// 
			this->Tvprysk->Location = System::Drawing::Point(129, 204);
			this->Tvprysk->Name = L"Tvprysk";
			this->Tvprysk->Size = System::Drawing::Size(100, 20);
			this->Tvprysk->TabIndex = 7;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(235, 211);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(184, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Продолжительность впрыска, мкс";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(235, 60);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(123, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Режим работы СКАУД";
			// 
			// RPM
			// 
			this->RPM->Location = System::Drawing::Point(129, 91);
			this->RPM->Name = L"RPM";
			this->RPM->Size = System::Drawing::Size(100, 20);
			this->RPM->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(235, 98);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(146, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Частота вращения, об/мин";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->checkManLedOut);
			this->tabPage2->Controls->Add(this->checkManLedIn);
			this->tabPage2->Controls->Add(this->checkCanTimeOut);
			this->tabPage2->Controls->Add(this->checkCanTimeIn);
			this->tabPage2->Controls->Add(this->dT_ms);
			this->tabPage2->Controls->Add(this->label2);
			this->tabPage2->Controls->Add(this->label26);
			this->tabPage2->Controls->Add(this->label25);
			this->tabPage2->Controls->Add(this->label24);
			this->tabPage2->Controls->Add(this->textIntTime1);
			this->tabPage2->Controls->Add(this->textIntTime);
			this->tabPage2->Controls->Add(this->checkManQCtIn);
			this->tabPage2->Controls->Add(this->checkManQCtOut);
			this->tabPage2->Controls->Add(this->gridFdbk);
			this->tabPage2->Controls->Add(this->textProgTime);
			this->tabPage2->Controls->Add(this->checkManFdbkOut);
			this->tabPage2->Controls->Add(this->checkManFdbkIn);
			this->tabPage2->Controls->Add(this->label22);
			this->tabPage2->Controls->Add(this->textinjUOVTOut);
			this->tabPage2->Controls->Add(this->textinjUOVTIn);
			this->tabPage2->Controls->Add(this->label21);
			this->tabPage2->Controls->Add(this->textmanNOut);
			this->tabPage2->Controls->Add(this->textmanNIn);
			this->tabPage2->Controls->Add(this->label20);
			this->tabPage2->Controls->Add(this->textQCAnOut);
			this->tabPage2->Controls->Add(this->textQCAnIn);
			this->tabPage2->Controls->Add(this->label19);
			this->tabPage2->Controls->Add(this->textQCtOut);
			this->tabPage2->Controls->Add(this->textQCtIn);
			this->tabPage2->Controls->Add(this->checkManModeOut);
			this->tabPage2->Controls->Add(this->checkmanUOVTOut);
			this->tabPage2->Controls->Add(this->checkmanUOVTIn);
			this->tabPage2->Controls->Add(this->checkCanSendOut);
			this->tabPage2->Controls->Add(this->checkmanPedOut);
			this->tabPage2->Controls->Add(this->checkinjOnceOut);
			this->tabPage2->Controls->Add(this->checkmanInjOut);
			this->tabPage2->Controls->Add(this->checkCanSendIn);
			this->tabPage2->Controls->Add(this->checkmanPedIn);
			this->tabPage2->Controls->Add(this->checkinjOnceIn);
			this->tabPage2->Controls->Add(this->checkmanInjIn);
			this->tabPage2->Controls->Add(this->checkmanAngleIn);
			this->tabPage2->Controls->Add(this->checkmanQCIn);
			this->tabPage2->Controls->Add(this->textBox11);
			this->tabPage2->Controls->Add(this->checkManModeIn);
			this->tabPage2->Controls->Add(this->label13);
			this->tabPage2->Controls->Add(this->checkmanAngleOut);
			this->tabPage2->Controls->Add(this->checkmanQCOut);
			this->tabPage2->Controls->Add(this->label12);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(947, 638);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Ручной режим";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// checkManLedOut
			// 
			this->checkManLedOut->AutoSize = true;
			this->checkManLedOut->Location = System::Drawing::Point(591, 329);
			this->checkManLedOut->Name = L"checkManLedOut";
			this->checkManLedOut->Size = System::Drawing::Size(81, 17);
			this->checkManLedOut->TabIndex = 48;
			this->checkManLedOut->Text = L"manLedOut";
			this->checkManLedOut->UseVisualStyleBackColor = true;
			// 
			// checkManLedIn
			// 
			this->checkManLedIn->AutoSize = true;
			this->checkManLedIn->Location = System::Drawing::Point(465, 329);
			this->checkManLedIn->Name = L"checkManLedIn";
			this->checkManLedIn->Size = System::Drawing::Size(73, 17);
			this->checkManLedIn->TabIndex = 47;
			this->checkManLedIn->Text = L"manLedIn";
			this->checkManLedIn->UseVisualStyleBackColor = true;
			// 
			// checkCanTimeOut
			// 
			this->checkCanTimeOut->AutoSize = true;
			this->checkCanTimeOut->Location = System::Drawing::Point(591, 271);
			this->checkCanTimeOut->Name = L"checkCanTimeOut";
			this->checkCanTimeOut->Size = System::Drawing::Size(85, 17);
			this->checkCanTimeOut->TabIndex = 46;
			this->checkCanTimeOut->Text = L"CanTimeOut";
			this->checkCanTimeOut->UseVisualStyleBackColor = true;
			// 
			// checkCanTimeIn
			// 
			this->checkCanTimeIn->AutoSize = true;
			this->checkCanTimeIn->Location = System::Drawing::Point(465, 271);
			this->checkCanTimeIn->Name = L"checkCanTimeIn";
			this->checkCanTimeIn->Size = System::Drawing::Size(77, 17);
			this->checkCanTimeIn->TabIndex = 45;
			this->checkCanTimeIn->Text = L"CanTimeIn";
			this->checkCanTimeIn->UseVisualStyleBackColor = true;
			// 
			// dT_ms
			// 
			this->dT_ms->Location = System::Drawing::Point(463, 471);
			this->dT_ms->Name = L"dT_ms";
			this->dT_ms->Size = System::Drawing::Size(100, 20);
			this->dT_ms->TabIndex = 44;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(571, 474);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(226, 13);
			this->label2->TabIndex = 43;
			this->label2->Text = L"Промежуток времени между зубьями, мкс";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(571, 527);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(269, 13);
			this->label26->TabIndex = 42;
			this->label26->Text = L"Время прерывания TIM1 (впрыск) (частота 100мкс)";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(571, 500);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(177, 13);
			this->label25->TabIndex = 41;
			this->label25->Text = L"Время прерывания XINT1 (зубья)";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(571, 448);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(142, 13);
			this->label24->TabIndex = 40;
			this->label24->Text = L"Время работы программы";
			// 
			// textIntTime1
			// 
			this->textIntTime1->Location = System::Drawing::Point(463, 523);
			this->textIntTime1->Name = L"textIntTime1";
			this->textIntTime1->Size = System::Drawing::Size(100, 20);
			this->textIntTime1->TabIndex = 39;
			// 
			// textIntTime
			// 
			this->textIntTime->Location = System::Drawing::Point(463, 497);
			this->textIntTime->Name = L"textIntTime";
			this->textIntTime->Size = System::Drawing::Size(100, 20);
			this->textIntTime->TabIndex = 38;
			// 
			// checkManQCtIn
			// 
			this->checkManQCtIn->AutoSize = true;
			this->checkManQCtIn->Location = System::Drawing::Point(21, 85);
			this->checkManQCtIn->Name = L"checkManQCtIn";
			this->checkManQCtIn->Size = System::Drawing::Size(73, 17);
			this->checkManQCtIn->TabIndex = 37;
			this->checkManQCtIn->Text = L"manQCtIn";
			this->checkManQCtIn->UseVisualStyleBackColor = true;
			// 
			// checkManQCtOut
			// 
			this->checkManQCtOut->AutoSize = true;
			this->checkManQCtOut->Location = System::Drawing::Point(147, 85);
			this->checkManQCtOut->Name = L"checkManQCtOut";
			this->checkManQCtOut->Size = System::Drawing::Size(81, 17);
			this->checkManQCtOut->TabIndex = 36;
			this->checkManQCtOut->Text = L"manQCtOut";
			this->checkManQCtOut->UseVisualStyleBackColor = true;
			// 
			// gridFdbk
			// 
			this->gridFdbk->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
			this->gridFdbk->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridFdbk->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(51) {this->Column1, this->Column2, 
				this->Column3, this->Column4, this->Column5, this->Column6, this->Column7, this->Column8, this->Column9, this->Column10, this->Column11, 
				this->Column12, this->Column13, this->Column14, this->Column15, this->Column16, this->Column17, this->Column18, this->Column19, 
				this->Column20, this->Column21, this->Column22, this->Column23, this->Column24, this->Column25, this->Column26, this->Column27, 
				this->Column28, this->Column29, this->Column30, this->Column31, this->Column32, this->Column33, this->Column34, this->Column35, 
				this->Column36, this->Column37, this->Column38, this->Column39, this->Column40, this->Column41, this->Column42, this->Column43, 
				this->Column44, this->Column45, this->Column46, this->Column47, this->Column48, this->Column49, this->Column50, this->Column51});
			this->gridFdbk->EnableHeadersVisualStyles = false;
			this->gridFdbk->Location = System::Drawing::Point(21, 467);
			this->gridFdbk->Name = L"gridFdbk";
			this->gridFdbk->Size = System::Drawing::Size(436, 55);
			this->gridFdbk->TabIndex = 35;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Column1";
			this->Column1->Name = L"Column1";
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Column2";
			this->Column2->Name = L"Column2";
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Column3";
			this->Column3->Name = L"Column3";
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Column4";
			this->Column4->Name = L"Column4";
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Column5";
			this->Column5->Name = L"Column5";
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"Column6";
			this->Column6->Name = L"Column6";
			// 
			// Column7
			// 
			this->Column7->HeaderText = L"Column7";
			this->Column7->Name = L"Column7";
			// 
			// Column8
			// 
			this->Column8->HeaderText = L"Column8";
			this->Column8->Name = L"Column8";
			// 
			// Column9
			// 
			this->Column9->HeaderText = L"Column9";
			this->Column9->Name = L"Column9";
			// 
			// Column10
			// 
			this->Column10->HeaderText = L"Column10";
			this->Column10->Name = L"Column10";
			// 
			// Column11
			// 
			this->Column11->HeaderText = L"Column11";
			this->Column11->Name = L"Column11";
			// 
			// Column12
			// 
			this->Column12->HeaderText = L"Column12";
			this->Column12->Name = L"Column12";
			// 
			// Column13
			// 
			this->Column13->HeaderText = L"Column13";
			this->Column13->Name = L"Column13";
			// 
			// Column14
			// 
			this->Column14->HeaderText = L"Column14";
			this->Column14->Name = L"Column14";
			// 
			// Column15
			// 
			this->Column15->HeaderText = L"Column15";
			this->Column15->Name = L"Column15";
			// 
			// Column16
			// 
			this->Column16->HeaderText = L"Column16";
			this->Column16->Name = L"Column16";
			// 
			// Column17
			// 
			this->Column17->HeaderText = L"Column17";
			this->Column17->Name = L"Column17";
			// 
			// Column18
			// 
			this->Column18->HeaderText = L"Column18";
			this->Column18->Name = L"Column18";
			// 
			// Column19
			// 
			this->Column19->HeaderText = L"Column19";
			this->Column19->Name = L"Column19";
			// 
			// Column20
			// 
			this->Column20->HeaderText = L"Column20";
			this->Column20->Name = L"Column20";
			// 
			// Column21
			// 
			this->Column21->HeaderText = L"Column21";
			this->Column21->Name = L"Column21";
			// 
			// Column22
			// 
			this->Column22->HeaderText = L"Column22";
			this->Column22->Name = L"Column22";
			// 
			// Column23
			// 
			this->Column23->HeaderText = L"Column23";
			this->Column23->Name = L"Column23";
			// 
			// Column24
			// 
			this->Column24->HeaderText = L"Column24";
			this->Column24->Name = L"Column24";
			// 
			// Column25
			// 
			this->Column25->HeaderText = L"Column25";
			this->Column25->Name = L"Column25";
			// 
			// Column26
			// 
			this->Column26->HeaderText = L"Column26";
			this->Column26->Name = L"Column26";
			// 
			// Column27
			// 
			this->Column27->HeaderText = L"Column27";
			this->Column27->Name = L"Column27";
			// 
			// Column28
			// 
			this->Column28->HeaderText = L"Column28";
			this->Column28->Name = L"Column28";
			// 
			// Column29
			// 
			this->Column29->HeaderText = L"Column29";
			this->Column29->Name = L"Column29";
			// 
			// Column30
			// 
			this->Column30->HeaderText = L"Column30";
			this->Column30->Name = L"Column30";
			// 
			// Column31
			// 
			this->Column31->HeaderText = L"Column31";
			this->Column31->Name = L"Column31";
			// 
			// Column32
			// 
			this->Column32->HeaderText = L"Column32";
			this->Column32->Name = L"Column32";
			// 
			// Column33
			// 
			this->Column33->HeaderText = L"Column33";
			this->Column33->Name = L"Column33";
			// 
			// Column34
			// 
			this->Column34->HeaderText = L"Column34";
			this->Column34->Name = L"Column34";
			// 
			// Column35
			// 
			this->Column35->HeaderText = L"Column35";
			this->Column35->Name = L"Column35";
			// 
			// Column36
			// 
			this->Column36->HeaderText = L"Column36";
			this->Column36->Name = L"Column36";
			// 
			// Column37
			// 
			this->Column37->HeaderText = L"Column37";
			this->Column37->Name = L"Column37";
			// 
			// Column38
			// 
			this->Column38->HeaderText = L"Column38";
			this->Column38->Name = L"Column38";
			// 
			// Column39
			// 
			this->Column39->HeaderText = L"Column39";
			this->Column39->Name = L"Column39";
			// 
			// Column40
			// 
			this->Column40->HeaderText = L"Column40";
			this->Column40->Name = L"Column40";
			// 
			// Column41
			// 
			this->Column41->HeaderText = L"Column41";
			this->Column41->Name = L"Column41";
			// 
			// Column42
			// 
			this->Column42->HeaderText = L"Column42";
			this->Column42->Name = L"Column42";
			// 
			// Column43
			// 
			this->Column43->HeaderText = L"Column43";
			this->Column43->Name = L"Column43";
			// 
			// Column44
			// 
			this->Column44->HeaderText = L"Column44";
			this->Column44->Name = L"Column44";
			// 
			// Column45
			// 
			this->Column45->HeaderText = L"Column45";
			this->Column45->Name = L"Column45";
			// 
			// Column46
			// 
			this->Column46->HeaderText = L"Column46";
			this->Column46->Name = L"Column46";
			// 
			// Column47
			// 
			this->Column47->HeaderText = L"Column47";
			this->Column47->Name = L"Column47";
			// 
			// Column48
			// 
			this->Column48->HeaderText = L"Column48";
			this->Column48->Name = L"Column48";
			// 
			// Column49
			// 
			this->Column49->HeaderText = L"Column49";
			this->Column49->Name = L"Column49";
			// 
			// Column50
			// 
			this->Column50->HeaderText = L"Column50";
			this->Column50->Name = L"Column50";
			// 
			// Column51
			// 
			this->Column51->HeaderText = L"Column51";
			this->Column51->Name = L"Column51";
			// 
			// textProgTime
			// 
			this->textProgTime->Location = System::Drawing::Point(463, 445);
			this->textProgTime->Name = L"textProgTime";
			this->textProgTime->Size = System::Drawing::Size(100, 20);
			this->textProgTime->TabIndex = 34;
			this->textProgTime->Text = L"0";
			// 
			// checkManFdbkOut
			// 
			this->checkManFdbkOut->AutoSize = true;
			this->checkManFdbkOut->Location = System::Drawing::Point(148, 419);
			this->checkManFdbkOut->Name = L"checkManFdbkOut";
			this->checkManFdbkOut->Size = System::Drawing::Size(87, 17);
			this->checkManFdbkOut->TabIndex = 33;
			this->checkManFdbkOut->Text = L"manFdbkOut";
			this->checkManFdbkOut->UseVisualStyleBackColor = true;
			// 
			// checkManFdbkIn
			// 
			this->checkManFdbkIn->AutoSize = true;
			this->checkManFdbkIn->Location = System::Drawing::Point(21, 419);
			this->checkManFdbkIn->Name = L"checkManFdbkIn";
			this->checkManFdbkIn->Size = System::Drawing::Size(79, 17);
			this->checkManFdbkIn->TabIndex = 32;
			this->checkManFdbkIn->Text = L"manFdbkIn";
			this->checkManFdbkIn->UseVisualStyleBackColor = true;
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(525, 367);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(83, 13);
			this->label22->TabIndex = 31;
			this->label22->Text = L"Задание УОВТ";
			// 
			// textinjUOVTOut
			// 
			this->textinjUOVTOut->Location = System::Drawing::Point(589, 384);
			this->textinjUOVTOut->Name = L"textinjUOVTOut";
			this->textinjUOVTOut->Size = System::Drawing::Size(100, 20);
			this->textinjUOVTOut->TabIndex = 30;
			this->textinjUOVTOut->Text = L"0";
			// 
			// textinjUOVTIn
			// 
			this->textinjUOVTIn->Location = System::Drawing::Point(463, 384);
			this->textinjUOVTIn->Name = L"textinjUOVTIn";
			this->textinjUOVTIn->Size = System::Drawing::Size(100, 20);
			this->textinjUOVTIn->TabIndex = 29;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(32, 351);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(215, 13);
			this->label21->TabIndex = 28;
			this->label21->Text = L"Задание частоты следования импульсов";
			// 
			// textmanNOut
			// 
			this->textmanNOut->Location = System::Drawing::Point(147, 367);
			this->textmanNOut->Name = L"textmanNOut";
			this->textmanNOut->Size = System::Drawing::Size(100, 20);
			this->textmanNOut->TabIndex = 27;
			this->textmanNOut->Text = L"0";
			// 
			// textmanNIn
			// 
			this->textmanNIn->Location = System::Drawing::Point(21, 367);
			this->textmanNIn->Name = L"textmanNIn";
			this->textmanNIn->Size = System::Drawing::Size(100, 20);
			this->textmanNIn->TabIndex = 26;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(81, 227);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(75, 13);
			this->label20->TabIndex = 25;
			this->label20->Text = L"Задание угла";
			// 
			// textQCAnOut
			// 
			this->textQCAnOut->Location = System::Drawing::Point(147, 243);
			this->textQCAnOut->Name = L"textQCAnOut";
			this->textQCAnOut->Size = System::Drawing::Size(100, 20);
			this->textQCAnOut->TabIndex = 24;
			this->textQCAnOut->Text = L"0";
			// 
			// textQCAnIn
			// 
			this->textQCAnIn->Location = System::Drawing::Point(21, 243);
			this->textQCAnIn->Name = L"textQCAnIn";
			this->textQCAnIn->Size = System::Drawing::Size(100, 20);
			this->textQCAnIn->TabIndex = 23;
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(41, 137);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(181, 13);
			this->label19->TabIndex = 22;
			this->label19->Text = L"Задание продолжительности, мкс";
			// 
			// textQCtOut
			// 
			this->textQCtOut->Location = System::Drawing::Point(147, 153);
			this->textQCtOut->Name = L"textQCtOut";
			this->textQCtOut->Size = System::Drawing::Size(100, 20);
			this->textQCtOut->TabIndex = 21;
			this->textQCtOut->Text = L"0";
			// 
			// textQCtIn
			// 
			this->textQCtIn->Location = System::Drawing::Point(21, 153);
			this->textQCtIn->Name = L"textQCtIn";
			this->textQCtIn->Size = System::Drawing::Size(100, 20);
			this->textQCtIn->TabIndex = 20;
			// 
			// checkManModeOut
			// 
			this->checkManModeOut->AutoSize = true;
			this->checkManModeOut->Location = System::Drawing::Point(591, 57);
			this->checkManModeOut->Name = L"checkManModeOut";
			this->checkManModeOut->Size = System::Drawing::Size(91, 17);
			this->checkManModeOut->TabIndex = 19;
			this->checkManModeOut->Text = L"ManModeOut";
			this->checkManModeOut->UseVisualStyleBackColor = true;
			// 
			// checkmanUOVTOut
			// 
			this->checkmanUOVTOut->AutoSize = true;
			this->checkmanUOVTOut->Location = System::Drawing::Point(591, 301);
			this->checkmanUOVTOut->Name = L"checkmanUOVTOut";
			this->checkmanUOVTOut->Size = System::Drawing::Size(93, 17);
			this->checkmanUOVTOut->TabIndex = 18;
			this->checkmanUOVTOut->Text = L"manUOVTOut";
			this->checkmanUOVTOut->UseVisualStyleBackColor = true;
			this->checkmanUOVTOut->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkmanUOVTOut_CheckedChanged);
			// 
			// checkmanUOVTIn
			// 
			this->checkmanUOVTIn->AutoSize = true;
			this->checkmanUOVTIn->Location = System::Drawing::Point(465, 301);
			this->checkmanUOVTIn->Name = L"checkmanUOVTIn";
			this->checkmanUOVTIn->Size = System::Drawing::Size(85, 17);
			this->checkmanUOVTIn->TabIndex = 17;
			this->checkmanUOVTIn->Text = L"manUOVTIn";
			this->checkmanUOVTIn->UseVisualStyleBackColor = true;
			this->checkmanUOVTIn->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkmanUOVTIn_CheckedChanged);
			// 
			// checkCanSendOut
			// 
			this->checkCanSendOut->AutoSize = true;
			this->checkCanSendOut->Location = System::Drawing::Point(591, 239);
			this->checkCanSendOut->Name = L"checkCanSendOut";
			this->checkCanSendOut->Size = System::Drawing::Size(87, 17);
			this->checkCanSendOut->TabIndex = 16;
			this->checkCanSendOut->Text = L"CanSendOut";
			this->checkCanSendOut->UseVisualStyleBackColor = true;
			// 
			// checkmanPedOut
			// 
			this->checkmanPedOut->AutoSize = true;
			this->checkmanPedOut->Location = System::Drawing::Point(592, 207);
			this->checkmanPedOut->Name = L"checkmanPedOut";
			this->checkmanPedOut->Size = System::Drawing::Size(82, 17);
			this->checkmanPedOut->TabIndex = 15;
			this->checkmanPedOut->Text = L"manPedOut";
			this->checkmanPedOut->UseVisualStyleBackColor = true;
			// 
			// checkinjOnceOut
			// 
			this->checkinjOnceOut->AutoSize = true;
			this->checkinjOnceOut->Location = System::Drawing::Point(148, 321);
			this->checkinjOnceOut->Name = L"checkinjOnceOut";
			this->checkinjOnceOut->Size = System::Drawing::Size(79, 17);
			this->checkinjOnceOut->TabIndex = 14;
			this->checkinjOnceOut->Text = L"injOnceOut";
			this->checkinjOnceOut->UseVisualStyleBackColor = true;
			// 
			// checkmanInjOut
			// 
			this->checkmanInjOut->AutoSize = true;
			this->checkmanInjOut->Location = System::Drawing::Point(148, 280);
			this->checkmanInjOut->Name = L"checkmanInjOut";
			this->checkmanInjOut->Size = System::Drawing::Size(74, 17);
			this->checkmanInjOut->TabIndex = 13;
			this->checkmanInjOut->Text = L"manInjOut";
			this->checkmanInjOut->UseVisualStyleBackColor = true;
			// 
			// checkCanSendIn
			// 
			this->checkCanSendIn->AutoSize = true;
			this->checkCanSendIn->Location = System::Drawing::Point(465, 239);
			this->checkCanSendIn->Name = L"checkCanSendIn";
			this->checkCanSendIn->Size = System::Drawing::Size(79, 17);
			this->checkCanSendIn->TabIndex = 12;
			this->checkCanSendIn->Text = L"CanSendIn";
			this->checkCanSendIn->UseVisualStyleBackColor = true;
			// 
			// checkmanPedIn
			// 
			this->checkmanPedIn->AutoSize = true;
			this->checkmanPedIn->Location = System::Drawing::Point(465, 207);
			this->checkmanPedIn->Name = L"checkmanPedIn";
			this->checkmanPedIn->Size = System::Drawing::Size(74, 17);
			this->checkmanPedIn->TabIndex = 11;
			this->checkmanPedIn->Text = L"manPedIn";
			this->checkmanPedIn->UseVisualStyleBackColor = true;
			// 
			// checkinjOnceIn
			// 
			this->checkinjOnceIn->AutoSize = true;
			this->checkinjOnceIn->Location = System::Drawing::Point(21, 321);
			this->checkinjOnceIn->Name = L"checkinjOnceIn";
			this->checkinjOnceIn->Size = System::Drawing::Size(71, 17);
			this->checkinjOnceIn->TabIndex = 10;
			this->checkinjOnceIn->Text = L"injOnceIn";
			this->checkinjOnceIn->UseVisualStyleBackColor = true;
			// 
			// checkmanInjIn
			// 
			this->checkmanInjIn->AutoSize = true;
			this->checkmanInjIn->Location = System::Drawing::Point(21, 280);
			this->checkmanInjIn->Name = L"checkmanInjIn";
			this->checkmanInjIn->Size = System::Drawing::Size(66, 17);
			this->checkmanInjIn->TabIndex = 9;
			this->checkmanInjIn->Text = L"manInjIn";
			this->checkmanInjIn->UseVisualStyleBackColor = true;
			// 
			// checkmanAngleIn
			// 
			this->checkmanAngleIn->AutoSize = true;
			this->checkmanAngleIn->Location = System::Drawing::Point(21, 198);
			this->checkmanAngleIn->Name = L"checkmanAngleIn";
			this->checkmanAngleIn->Size = System::Drawing::Size(82, 17);
			this->checkmanAngleIn->TabIndex = 8;
			this->checkmanAngleIn->Text = L"manAngleIn";
			this->checkmanAngleIn->UseVisualStyleBackColor = true;
			// 
			// checkmanQCIn
			// 
			this->checkmanQCIn->AutoSize = true;
			this->checkmanQCIn->Location = System::Drawing::Point(21, 62);
			this->checkmanQCIn->Name = L"checkmanQCIn";
			this->checkmanQCIn->Size = System::Drawing::Size(70, 17);
			this->checkmanQCIn->TabIndex = 7;
			this->checkmanQCIn->Text = L"manQCIn";
			this->checkmanQCIn->UseVisualStyleBackColor = true;
			// 
			// textBox11
			// 
			this->textBox11->Location = System::Drawing::Point(465, 78);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(100, 20);
			this->textBox11->TabIndex = 6;
			// 
			// checkManModeIn
			// 
			this->checkManModeIn->AutoSize = true;
			this->checkManModeIn->Location = System::Drawing::Point(465, 57);
			this->checkManModeIn->Name = L"checkManModeIn";
			this->checkManModeIn->Size = System::Drawing::Size(83, 17);
			this->checkManModeIn->TabIndex = 5;
			this->checkManModeIn->Text = L"ManModeIn";
			this->checkManModeIn->UseVisualStyleBackColor = true;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(462, 27);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(120, 13);
			this->label13->TabIndex = 4;
			this->label13->Text = L"Управление режимом";
			// 
			// checkmanAngleOut
			// 
			this->checkmanAngleOut->AutoSize = true;
			this->checkmanAngleOut->Location = System::Drawing::Point(147, 198);
			this->checkmanAngleOut->Name = L"checkmanAngleOut";
			this->checkmanAngleOut->Size = System::Drawing::Size(90, 17);
			this->checkmanAngleOut->TabIndex = 3;
			this->checkmanAngleOut->Text = L"manAngleOut";
			this->checkmanAngleOut->UseVisualStyleBackColor = true;
			// 
			// checkmanQCOut
			// 
			this->checkmanQCOut->AutoSize = true;
			this->checkmanQCOut->Location = System::Drawing::Point(147, 62);
			this->checkmanQCOut->Name = L"checkmanQCOut";
			this->checkmanQCOut->Size = System::Drawing::Size(78, 17);
			this->checkmanQCOut->TabIndex = 2;
			this->checkmanQCOut->Text = L"manQCOut";
			this->checkmanQCOut->UseVisualStyleBackColor = true;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(43, 27);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(113, 13);
			this->label12->TabIndex = 1;
			this->label12->Text = L"Управление подачей";
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->textInjD2Out);
			this->tabPage3->Controls->Add(this->textInjD1Out);
			this->tabPage3->Controls->Add(this->textInjT2Out);
			this->tabPage3->Controls->Add(this->textInjT1Out);
			this->tabPage3->Controls->Add(this->textInjD2In);
			this->tabPage3->Controls->Add(this->label16);
			this->tabPage3->Controls->Add(this->textInjD1In);
			this->tabPage3->Controls->Add(this->label17);
			this->tabPage3->Controls->Add(this->textInjT2In);
			this->tabPage3->Controls->Add(this->label15);
			this->tabPage3->Controls->Add(this->textInjT1In);
			this->tabPage3->Controls->Add(this->label14);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(947, 638);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Системные настройки";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// textInjD2Out
			// 
			this->textInjD2Out->Location = System::Drawing::Point(458, 110);
			this->textInjD2Out->Name = L"textInjD2Out";
			this->textInjD2Out->Size = System::Drawing::Size(100, 20);
			this->textInjD2Out->TabIndex = 11;
			// 
			// textInjD1Out
			// 
			this->textInjD1Out->Location = System::Drawing::Point(170, 110);
			this->textInjD1Out->Name = L"textInjD1Out";
			this->textInjD1Out->Size = System::Drawing::Size(100, 20);
			this->textInjD1Out->TabIndex = 10;
			// 
			// textInjT2Out
			// 
			this->textInjT2Out->Location = System::Drawing::Point(458, 60);
			this->textInjT2Out->Name = L"textInjT2Out";
			this->textInjT2Out->Size = System::Drawing::Size(100, 20);
			this->textInjT2Out->TabIndex = 9;
			// 
			// textInjT1Out
			// 
			this->textInjT1Out->Location = System::Drawing::Point(170, 60);
			this->textInjT1Out->Name = L"textInjT1Out";
			this->textInjT1Out->Size = System::Drawing::Size(100, 20);
			this->textInjT1Out->TabIndex = 8;
			// 
			// textInjD2In
			// 
			this->textInjD2In->Location = System::Drawing::Point(352, 110);
			this->textInjD2In->Name = L"textInjD2In";
			this->textInjD2In->Size = System::Drawing::Size(100, 20);
			this->textInjD2In->TabIndex = 7;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(412, 94);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(80, 13);
			this->label16->TabIndex = 6;
			this->label16->Text = L"Скважность У";
			// 
			// textInjD1In
			// 
			this->textInjD1In->Location = System::Drawing::Point(64, 111);
			this->textInjD1In->Name = L"textInjD1In";
			this->textInjD1In->Size = System::Drawing::Size(100, 20);
			this->textInjD1In->TabIndex = 5;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(124, 94);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(83, 13);
			this->label17->TabIndex = 4;
			this->label17->Text = L"Скважность Ф";
			// 
			// textInjT2In
			// 
			this->textInjT2In->Location = System::Drawing::Point(352, 60);
			this->textInjT2In->Name = L"textInjT2In";
			this->textInjT2In->Size = System::Drawing::Size(100, 20);
			this->textInjT2In->TabIndex = 3;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(390, 44);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(122, 13);
			this->label15->TabIndex = 2;
			this->label15->Text = L"Продолжительность У";
			// 
			// textInjT1In
			// 
			this->textInjT1In->Location = System::Drawing::Point(64, 61);
			this->textInjT1In->Name = L"textInjT1In";
			this->textInjT1In->Size = System::Drawing::Size(100, 20);
			this->textInjT1In->TabIndex = 1;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(102, 44);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(125, 13);
			this->label14->TabIndex = 0;
			this->label14->Text = L"Продолжительность Ф";
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->label29);
			this->tabPage4->Controls->Add(this->FilterTextBox);
			this->tabPage4->Controls->Add(this->ParametersDataGrid);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(947, 638);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"tabPage4";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// ParametersDataGrid
			// 
			this->ParametersDataGrid->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::DisplayedCells;
			this->ParametersDataGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->ParametersDataGrid->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->ParametersDataGrid->Location = System::Drawing::Point(3, 49);
			this->ParametersDataGrid->Name = L"ParametersDataGrid";
			this->ParametersDataGrid->ReadOnly = true;
			this->ParametersDataGrid->Size = System::Drawing::Size(941, 586);
			this->ParametersDataGrid->TabIndex = 0;
			this->ParametersDataGrid->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::ParametersDataGrid_CellClick);
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
			// FilterTextBox
			// 
			this->FilterTextBox->Location = System::Drawing::Point(10, 23);
			this->FilterTextBox->Name = L"FilterTextBox";
			this->FilterTextBox->Size = System::Drawing::Size(101, 20);
			this->FilterTextBox->TabIndex = 45;
			this->FilterTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(126, 26);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(47, 13);
			this->label29->TabIndex = 46;
			this->label29->Text = L"Фильтр";
			this->label29->Click += gcnew System::EventHandler(this, &Form1::label29_Click_1);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->ClientSize = System::Drawing::Size(1183, 683);
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
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numVMTOut))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridFdbk))->EndInit();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ParametersDataGrid))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bindingSource1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->canParametersDataSet))->EndInit();
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
			 this->checkmanQCOut->Checked = this->checkmanQCIn->Checked;
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
};
}