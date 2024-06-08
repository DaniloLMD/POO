#include "../include/Interface.hpp"

std::string Interface::getName(){
  GtkEntry* entry = GTK_ENTRY(gtk_builder_get_object(this->getBuilder(), "name"));
  return gtk_entry_get_text (entry);
}

std::string Interface::getPassword(){
    GtkEntry* entry = GTK_ENTRY(gtk_builder_get_object(this->getBuilder(), "password"));
    return gtk_entry_get_text (entry);
}

void Interface::loadLoginScreen(){
  GtkStack* stack = GTK_STACK(gtk_builder_get_object(this->getBuilder(), "stack"));
  gtk_stack_set_visible_child_name(stack, "login");

  GtkWidget* name = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "name"));
  GtkWidget* password = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "password"));
  gtk_widget_set_name(name, "entryNormal");
  gtk_widget_set_name(password, "entryNormal");
  
  if(!lembrar){
    gtk_entry_set_text(GTK_ENTRY(name), "Name");
    gtk_entry_set_text(GTK_ENTRY(password), "password");
  }

}

void Interface::on_login_clicked(){
    if(login(this->getName(), this->getPassword())){
        this->setUsuario(new Usuario(getName()));
        GtkStack* stack = GTK_STACK(gtk_builder_get_object(this->getBuilder(), "stack"));
        gtk_stack_set_visible_child_name(stack, "home"); 
        loadHomeScreen();
    }
    else{
        GtkWidget* name = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "name"));
        GtkWidget* password = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "password"));
        
        if(!Usuario::isValid(getName())) gtk_widget_set_name(name, "entryWrong");
        gtk_widget_set_name(password, "entryWrong");
    }
}

void Interface::on_cadastrar_clicked(){
    std::string name = getName();
    std::string password = getPassword();

    if(cadastrar(name, password)){
        Usuario* u = new Usuario(name); 
        this->popup("Cadastro realizado", "");
        on_name_changed();
    }
    else{
        this->popup("Cadastro falhou", "usuário inválido ou já existente");
    }
}

void Interface::on_remember_toggled(){
  lembrar = !lembrar;
}

void Interface::on_name_changed(){
  GtkWidget* name = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "name"));
  GtkWidget* password = GTK_WIDGET(gtk_builder_get_object(this->getBuilder(), "password"));
  gtk_widget_set_name(name, "entryNormal");
  gtk_widget_set_name(password, "entryNormal");
}

void Interface::on_name_activate(){
  on_login_clicked();
}

void Interface::on_password_activate(){
  on_login_clicked();
}


#include <bits/stdc++.h>
bool Interface::login(std::string userName, std::string password) {
  std::ifstream file(LOGIN_DATA_FILE_PATH);
  if (!file.is_open()) {
    return false;
  }

  std::string data;
  while(getline(file, data)) {
    std::istringstream iss(data);
    std::string fileUserName, filePassword;

    if (getline(iss, fileUserName, ',') && getline(iss, filePassword)) {
      if (fileUserName == userName && filePassword == password) {
        return true;
      }
    }
  }

  return false;
}

bool Interface::cadastrar(std::string userName, std::string password) {
  if (Usuario::isValid(userName)) {
    return false;
  }
  if(!userName.size() || !password.size()) return false;

  FILE* ptr = fopen(LOGIN_DATA_FILE_PATH, "a");
  if(!ptr) return false;

  fprintf(ptr, "%s,%s\n", userName.c_str(), password.c_str());

  fclose(ptr);


  return true;
}