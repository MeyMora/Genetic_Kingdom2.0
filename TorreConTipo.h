#pragma once
#include <memory>
#include "Torre.h"
#include "TipoTorre.h"

struct TorreConTipo {
    std::unique_ptr<Torre> torre;
    TipoTorre tipo;

    TorreConTipo(std::unique_ptr<Torre> t, TipoTorre tipo_)
        : torre(std::move(t)), tipo(tipo_) {
    }
};
#pragma once
