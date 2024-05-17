//
// Created by jb030 on 04/05/2024.
//

#include "task_show.h"
#include <interface/table/task_ui.h>
#include <interface/table/task.h>
#include <interface/table/app_state.h>
#include <interface/table/task_relation.h>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>

std::vector<std::string> task_show::get_show_stack() {
    int64_t now_viewing_task_id = app_state::get_now_viewing_task();
    if (now_viewing_task_id == -1) {
        return {};
    }
    task::task_t task1 = task::get_task_by_id(now_viewing_task_id);
    std::vector<std::string> stack;
    stack.push_back(task1.name);
    while (task1.task_id != -1) {
        task1 = task::get_task_by_id(task1.parent_task);
        stack.push_back(task1.name);
    }
    stack.pop_back();
    return stack;
}

std::string task_show::node_type_to_string(task_show::node_type t) {
    switch (t) {
        case task_show::node_type::start:
            return "start";
        case task_show::node_type::end:
            return "end";
        case task_show::node_type::origin:
            return "origin";
        case task_show::node_type::task:
            return "task";
    }
}

task_show::show_data_t task_show::get_show_data() {
    int64_t now_viewing_task_id = app_state::get_now_viewing_task();
    if (now_viewing_task_id == -1) {
        return {};
    }
    return get_show_data_by_id(now_viewing_task_id);
}

std::tuple<std::vector<std::string>,std::vector<std::string>> inference_start_and_end_nodes(const std::vector<task_show::show_node_t>& nodes, const std::vector<task_relation::task_relation_t>& relations) {
    std::vector<std::string> node_connected_to_start;
    std::vector<std::string> node_connected_to_end;

    std::set<int64_t> source_set;
    std::set<int64_t> target_set;
    std::map<int64_t, bool> connected_map;
    for (auto & relation : relations) {
        source_set.insert(relation.source_task);
        target_set.insert(relation.target_task);
    }
    std::set<int64_t> intersection = {};
    std::set_intersection(source_set.begin(), source_set.end(), target_set.begin(), target_set.end(), std::inserter(intersection, intersection.begin()));
    std::set<int64_t> source_target = {};
    std::set_difference(source_set.begin(), source_set.end(), intersection.begin(), intersection.end(), std::inserter(source_target, source_target.begin()));
    std::set<int64_t> target_source = {};
    std::set_difference(target_set.begin(), target_set.end(), intersection.begin(), intersection.end(), std::inserter(target_source, target_source.begin()));

    for (auto & source : intersection) {
        connected_map[source] = true;
    }

    node_connected_to_start.reserve(source_target.size());
    for (auto & source : source_target) {
        node_connected_to_start.push_back(std::to_string(source));
        connected_map[source] = true;
    }

    node_connected_to_end.reserve(target_source.size());
    for (auto & target : target_source) {
        node_connected_to_end.push_back(std::to_string(target));
        connected_map[target] = true;
    }

    for (auto & node : nodes) {
        if (connected_map.find(std::stoll(node.id)) == connected_map.end()) {
            node_connected_to_start.push_back(node.id);
            node_connected_to_end.push_back(node.id);
        }
    }

    return {node_connected_to_start, node_connected_to_end};
}

task_show::show_data_t task_show::get_show_data_by_id(int64_t id) {
    std::vector<task::task_t> tasks = task::get_tasks_by_parent_task(id);
    std::vector<task_ui::task_ui_t> task_uis = task_ui::get_task_ui_by_parent_task(id);
    if (tasks.size() != task_uis.size()) {
        return {};
    }
    task_show::show_data_t show_data;
    for (int i = 0; i < tasks.size(); i++) {
        task_show::show_node_t node;
        node.id = std::to_string(tasks[i].task_id);
        node.name = tasks[i].name;
        node.position.x = task_uis[i].position_x;
        node.position.y = task_uis[i].position_y;
        show_data.nodes.push_back(std::move(node));
    }

    std::vector<task_relation::task_relation_t> relations = task_relation::get_relations_by_parent_task(id);
    for (auto & relation : relations) {
        task_show::show_edge_t edge;
        edge.source = std::to_string(relation.source_task);
        edge.target = std::to_string(relation.target_task);
        show_data.edges.push_back(std::move(edge));
    }

    auto [node_connected_to_start, node_connected_to_end] = inference_start_and_end_nodes(show_data.nodes, relations);
    show_data.node_connected_to_start = std::move(node_connected_to_start);
    show_data.node_connected_to_end = std::move(node_connected_to_end);

    return show_data;
}

task_show::show_data_t task_show::set_now_viewing_and_get_show_data(int64_t id) {
    app_state::set_now_viewing_task(id);
    return get_show_data_by_id(id);
}

std::string task_show::edge_type_to_string(task_show::edge_type t) {
    switch (t) {
        case task_show::edge_type::default_e:
            return "default_e";
    }
}

task_show::show_data_t::show_data_t() {
    nodes.clear();
    edges.clear();
    node_connected_to_start.clear();
    node_connected_to_end.clear();
}

task_show::show_data_t::~show_data_t() {
    nodes.clear();
    edges.clear();
    node_connected_to_start.clear();
    node_connected_to_end.clear();
}

task_show::show_data_t::show_data_t(task_show::show_data_t &&other)  noexcept {
    nodes = std::move(other.nodes);
    edges = std::move(other.edges);
    node_connected_to_start = std::move(other.node_connected_to_start);
    node_connected_to_end = std::move(other.node_connected_to_end);
}

task_show::show_data_t &task_show::show_data_t::operator=(task_show::show_data_t &&other) noexcept {
    if (this != &other) {
        nodes = std::move(other.nodes);
        edges = std::move(other.edges);
        node_connected_to_start = std::move(other.node_connected_to_start);
        node_connected_to_end = std::move(other.node_connected_to_end);
    }
    return *this;
}

crow::json::wvalue task_show::show_data_t::to_crow_json() {
    crow::json::wvalue json;
    std::vector<crow::json::wvalue> nodes_json;
    for (auto & node : nodes) {
        crow::json::wvalue node_json;
        node_json["id"] = node.id;
        node_json["name"] = node.name;
        crow::json::wvalue position_json;
        position_json["x"] = node.position.x;
        position_json["y"] = node.position.y;
        node_json["position"] = std::move(position_json);
        nodes_json.push_back(std::move(node_json));
    }
    json["nodes"] = std::move(nodes_json);

    std::vector<crow::json::wvalue> edges_json;
    for (auto & edge : edges) {
        crow::json::wvalue edge_json;
        edge_json["source"] = edge.source;
        edge_json["target"] = edge.target;
        edges_json.push_back(std::move(edge_json));
    }
    json["edges"] = std::move(edges_json);

    std::vector<std::string> node_connected_to_start_json;
    node_connected_to_start_json.reserve(node_connected_to_start.size());
    for (auto & node : node_connected_to_start) {
        node_connected_to_start_json.push_back(node);
    }
    json["node_connected_to_start"] = node_connected_to_start_json;

    std::vector<std::string> node_connected_to_end_json;
    node_connected_to_end_json.reserve(node_connected_to_end.size());
    for (auto & node : node_connected_to_end) {
        node_connected_to_end_json.push_back(node);
    }
    json["node_connected_to_end"] = node_connected_to_end_json;

    return json;
}

task_show::show_edge_t::show_edge_t() {
    source = "";
    target = "";
}

task_show::show_edge_t::~show_edge_t() {
    source = "";
    target = "";
}

task_show::show_edge_t::show_edge_t(task_show::show_edge_t &&other) noexcept {
    source = std::move(other.source);
    target = std::move(other.target);
}

task_show::show_edge_t &task_show::show_edge_t::operator=(task_show::show_edge_t &&other) noexcept {
    if (this != &other) {
        source = std::move(other.source);
        target = std::move(other.target);
    }
    return *this;
}

task_show::show_node_t::show_node_t() {
    id = "";
    name = "";
    position.x = 0;
    position.y = 0;
}

task_show::show_node_t::~show_node_t() {
    id = "";
    name = "";
    position.x = 0;
    position.y = 0;
}

task_show::show_node_t::show_node_t(task_show::show_node_t &&other) noexcept {
    id = std::move(other.id);
    name = std::move(other.name);
    position = other.position;
}

task_show::show_node_t &task_show::show_node_t::operator=(task_show::show_node_t &&other) noexcept {
    if (this != &other) {
        id = std::move(other.id);
        name = std::move(other.name);
        position = other.position;
    }
    return *this;
}

task_show::show_node_t::show_node_t(const task_show::show_node_t &other) {
    id = other.id;
    name = other.name;
    position = other.position;
}

task_show::position_t::position_t() {
    x = 0;
    y = 0;
}

task_show::position_t::~position_t() {
    x = 0;
    y = 0;
}

task_show::position_t::position_t(const task_show::position_t &other) {
    x = other.x;
    y = other.y;
}

task_show::position_t &task_show::position_t::operator=(const task_show::position_t &other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}
