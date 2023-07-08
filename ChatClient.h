
#pragma once
#include <string>
#include <msclr\marshal_cppstd.h>

void sendMessage(std::string message);

void setAuthenticated(bool value);

std::vector<std::string> getMessageList();

namespace ChatClient {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class ClientGUI : public System::Windows::Forms::Form
	{
	public:
		ClientGUI(void)
		{
			InitializeComponent();


		}

	protected:
		~ClientGUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::DialogResult^ dialogResult1;
	public:
	private: System::ComponentModel::IContainer^ components;
	private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(12, 392);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(488, 42);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &ClientGUI::richTextBox1_TextChanged);
			this->richTextBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ClientGUI::richTextBox1_OnKeyPress);
			// 
			// listView1
			// 
			this->listView1->BackColor = System::Drawing::Color::DarkGray;
			this->listView1->Cursor = System::Windows::Forms::Cursors::Default;
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(12, 12);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(488, 374);
			this->listView1->TabIndex = 2;
			this->listView1->UseCompatibleStateImageBehavior = false;
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &ClientGUI::timer1_Tick);
			// 
			// listBox1
			// 
			this->listBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 20;
			this->listBox1->Location = System::Drawing::Point(24, 21);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(462, 340);
			this->listBox1->TabIndex = 3;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &ClientGUI::listBox1_SelectedIndexChanged);
			// 
			// ClientGUI
			// 
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::DimGray;
			this->ClientSize = System::Drawing::Size(512, 446);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->richTextBox1);
			this->Name = L"ClientGUI";
			this->Text = L"Chatroom";
			this->Load += gcnew System::EventHandler(this, &ClientGUI::ClientGUI_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void ClientGUI_Load(System::Object^ sender, System::EventArgs^ e) {
	
	}
	private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void richTextBox1_OnKeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (char)Keys::Return) {
			std::string convertedText = msclr::interop::marshal_as<std::string>(richTextBox1->Text);
			sendMessage(convertedText.substr(0, convertedText.size() - 1));
			richTextBox1->Clear();
		}
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	

		for (std::string message : getMessageList()) {
			System::String^ messageStr = gcnew System::String(message.c_str());
			listBox1->Items->Add(messageStr);
			listBox1->SelectedIndex = listBox1->Items->Count - 1;
			listBox1->ClearSelected();
		}
	}

	private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
};

}
