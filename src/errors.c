#include "errors.h"

const char* load_error_to_string(LoadError err) {
    switch (err) {
        case LOAD_OK: return "Operação concluída com sucesso.";
        case LOAD_ERR_FILE_NOT_FOUND: return "Ficheiro não encontrado.";
        case LOAD_ERR_TOO_LONG_LINE: return "Linha excede tamanho máximo permitido.";
        case LOAD_ERR_FORMAT_INVALID: return "Formato inválido na matriz.";
        default: return "Erro desconhecido.";
    }
}
