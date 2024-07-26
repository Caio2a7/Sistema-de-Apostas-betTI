#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <optional>
#include "service/ParticipantsService.h"
#include "entities/ParticipantsEntity.h"
#include "enum/UserRoleEnum.h"

int main() {
    try {
        // Criar uma conexão com o banco de dados
        pqxx::connection conn("dbname=beti user=postgres password=root hostaddr=127.0.0.1 port=5432");
        ParticipantsService userService;
        // ParticipantsEntity user(0, "usuario5", "usuario5@email.com", "123", UserRoleEnum::USUARIO, 100);
        ParticipantsEntity entity(0, "Vasco", 2);

        // std::optional<ParticipantsEntity> userAuth = userService.authUser(&conn, "user1@email.com", "123456");
        userService.save(&conn, &entity);
        optional<vector<ParticipantsEntity>> userFindAll =  userService.findAll(&conn);
        std::optional<ParticipantsEntity> userId = userService.findById(&conn, 1);
        // std::optional<ParticipantsEntity> userEmail = userService.findByEmail(&conn, "user2@email.com");

        // cout << "UserAuth" << endl;
        // userAuth.value().toString();
        // cout << endl;
        cout << "UserId" << endl;
        userId.value().toString();
        cout << endl;
        // cout << "UserEmail" << endl;
        // userEmail.value().toString();
        // cout << endl;
        cout << "Users" << endl;
        for (const auto& user : userFindAll.value()) {
            user.toString();
            cout << endl;
        }
        cout << endl;


    } catch (const std::exception& e) {
        std::cerr << "Erro ao conectar com o banco de dados: " << e.what() << std::endl;
    }

    return 0;
}
