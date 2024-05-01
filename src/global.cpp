//
// Created by jb030 on 28/04/2024.
//

#include <global.h>

sqlite3 * global::db = nullptr;

const char * global::app_db_init_sql = "-- Drop the existing tasks table if it exists\n"
                                       "drop table if exists tasks;\n"
                                       "\n"
                                       "-- Create the updated tasks table\n"
                                       "create table if not exists task\n"
                                       "(\n"
                                       "  id             integer primary key autoincrement,\n"
                                       "  root_task      integer,\n"
                                       "  name           text,\n"
                                       "  goal           text,\n"
                                       "  deadline       timestamp,\n"
                                       "  in_work_time   boolean,\n"
                                       "  status         integer,\n"
                                       "  parent_task    integer\n"
                                       ");\n"
                                       "\n"
                                       "-- Create indices for the tasks table\n"
                                       "create index if not exists task_id_idx on task (id);\n"
                                       "create index if not exists task_root_task_idx on task (root_task);\n"
                                       "-- create index if not exists tasks_name_idx on tasks (name);\n"
                                       "insert into task (id, root_task, name, goal, deadline, in_work_time, status, parent_task)\n"
                                       "values (0, -1, 'Overall', 'Good Game', 4102405199, 0, 0, -1);\n"
                                       "\n"
                                       "-- Drop the existing task_relation table if it exists\n"
                                       "drop table if exists task_relation;\n"
                                       "\n"
                                       "-- Create the task_relation table\n"
                                       "create table if not exists task_relation\n"
                                       "(\n"
                                       "  source integer, -- the source task id\n"
                                       "  target integer,  -- the target task id\n"
                                       "  primary key (source, target)\n"
                                       ");\n"
                                       "\n"
                                       "-- Create indices for the task_relation table\n"
                                       "create index if not exists task_relation_source_idx on task_relation (source);\n"
                                       "create index if not exists task_relation_target_idx on task_relation (target);\n"
                                       "\n"
                                       "-- Drop the existing task_trigger table if it exists\n"
                                       "drop table if exists task_trigger;\n"
                                       "\n"
                                       "-- Create the task_trigger table\n"
                                       "create table if not exists task_trigger\n"
                                       "(\n"
                                       "  id   integer primary key,\n"
                                       "  type integer,\n"
                                       "  info json\n"
                                       ");\n"
                                       "\n"
                                       "-- Create an index for the task_trigger table on the type column\n"
                                       "create index if not exists task_trigger_type_idx on task_trigger (type);\n"
                                       "\n"
                                       "-- Drop the existing task_after_effect table if it exists\n"
                                       "drop table if exists task_after_effect;\n"
                                       "\n"
                                       "-- Create the task_after_effect table\n"
                                       "create table if not exists task_after_effect\n"
                                       "(\n"
                                       "  id   integer primary key,\n"
                                       "  type integer,\n"
                                       "  info json\n"
                                       ");\n"
                                       "\n"
                                       "-- Create an index for the task_after_effect table on the type column\n"
                                       "create index if not exists task_after_effect_type_idx on task_after_effect (type);\n"
                                       "\n"
                                       "-- Drop the existing root_task table if it exists\n"
                                       "drop table if exists root_task;\n"
                                       "\n"
                                       "-- Create the root_task table\n"
                                       "create table if not exists root_task\n"
                                       "(\n"
                                       "  id integer primary key\n"
                                       ");\n"
                                       "\n"
                                       "-- Drop the existing suspended_task table if it exists\n"
                                       "drop table if exists suspended_task;\n"
                                       "\n"
                                       "-- Create the suspended_task table\n"
                                       "create table if not exists suspended_task\n"
                                       "(\n"
                                       "  id   integer primary key,\n"
                                       "  type integer,\n"
                                       "  info json\n"
                                       ");\n"
                                       "\n"
                                       "-- Create an index for the suspended_task table on the type column\n"
                                       "create index if not exists suspended_task_type_idx on suspended_task (type);\n"
                                       "\n"
                                       "-- Drop the existing app_state table if it exists\n"
                                       "drop table if exists app_state;\n"
                                       "\n"
                                       "-- Create the app_state table\n"
                                       "create table if not exists app_state\n"
                                       "(\n"
                                       "  id                integer primary key check (id = 0),\n"
                                       "  root_task         integer,\n"
                                       "  now_viewing_task  integer,\n"
                                       "  now_selected_task integer\n"
                                       ");\n"
                                       "\n"
                                       "-- Insert the initial singleton record\n"
                                       "insert into app_state (id, root_task, now_viewing_task, now_selected_task)\n"
                                       "VALUES (0, NULL, NULL, NULL);\n"
                                       "\n"
                                       "-- Drop the existing task_ui table if it exists\n"
                                       "drop table if exists task_ui;\n"
                                       "\n"
                                       "-- Create the task_ui table\n"
                                       "create table if not exists task_ui\n"
                                       "(\n"
                                       "  id     integer primary key,\n"
                                       "  parent_task integer,\n"
                                       "  position_x  integer,\n"
                                       "  position_y  integer\n"
                                       ");";
