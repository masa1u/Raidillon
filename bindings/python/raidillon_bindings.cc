#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "database.h"
#include "collection.h"
#include "index.h"

namespace py = pybind11;

PYBIND11_MODULE(raidillon_bindings, m) {
    py::class_<Raidillon::Database>(m, "Database")
        .def(py::init<const std::string&>())
        .def("createCollection", &Raidillon::Database::createCollection, py::return_value_policy::reference_internal);

    py::class_<Raidillon::Collection>(m, "Collection")
        .def(py::init<const std::string&>())
        .def("insert", py::overload_cast<const std::vector<float>&>(&Raidillon::Collection::insert))
        .def("insert", py::overload_cast<int, const std::vector<float>&>(&Raidillon::Collection::insert))
        .def("buildIndex", py::overload_cast<const std::string&, const std::string&>(&Raidillon::Collection::buildIndex), py::return_value_policy::reference_internal)
        .def("buildIndex", py::overload_cast<const std::string&, const std::string&, int>(&Raidillon::Collection::buildIndex), py::return_value_policy::reference_internal);

    py::class_<Raidillon::Index>(m, "Index")
        .def("search", &Raidillon::Index::search, py::arg("query"), py::arg("top_k"), py::arg("nprobe") = 1);
}