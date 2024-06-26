#ifndef __GERENCIADOR_NOTIFICACOES_HPP__
#define __GERENCIADOR_NOTIFICACOES_HPP__

#include <vector>

class Usuario; //declaração do usuario para poder compilar

class GerenciadorNotificacoes{
    public:
        GerenciadorNotificacoes(Usuario* usuario);

        void adicionar(Usuario* notificavel);

        void notificarTodos(std::string msg);

    private:
        std::vector<Usuario*> notificaveis;
        Usuario* usuario;
};

#endif