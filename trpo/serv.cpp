#include <microhttpd.h>
#include <iostream>
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>

using namespace std;

// Функция для генерации случайных вопросов
vector<string> generateRandomQuestions() {
    vector<string> questions;
    for (int i = 0; i < 2; i++) {
        questions.push_back("Вопрос " + to_string(i + 1));
    }
    return questions;
}

// Функция для обработки запросов от клиента
static int requestHandler(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    const char *page = "{}"; // Пустой JSON для начала

    // Генерируем случайные вопросы
    vector<string> questions = generateRandomQuestions();

    // Преобразуем вопросы в формат JSON
    Json::Value root;
    for (size_t i = 0; i < questions.size(); i++) {
        root["questions"][to_string(i)] = questions[i];
    }
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";
    page = Json::writeString(builder, root).c_str();

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                               &requestHandler, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    cout << "Сервер запущен на порту 8080..." << endl;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}
