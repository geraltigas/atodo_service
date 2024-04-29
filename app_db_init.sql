-- Drop the existing tasks table if it exists
drop table if exists tasks;

-- Create the updated tasks table
create table if not exists tasks
(
  id             timestamp primary key,
  root_task      timestamp,
  name           text,
  goal           text,
  deadline       timestamp,
  in_work_time   boolean,
  status         text check ( status in ('created', 'in_progress', 'paused', 'suspended', 'done')),
  parent_task    timestamp
);

-- Create indices for the tasks table
create index if not exists tasks_id_idx on tasks (id);
create index if not exists tasks_root_task_idx on tasks (root_task);
-- create index if not exists tasks_name_idx on tasks (name);

-- Drop the existing task_relation table if it exists
drop table if exists task_relation;

-- Create the task_relation table
create table if not exists task_relation
(
  id     text primary key,
  source timestamp,
  target timestamp
);

-- Create indices for the task_relation table
create index if not exists task_relation_source_idx on task_relation (source);
create index if not exists task_relation_target_idx on task_relation (target);

-- Drop the existing task_trigger table if it exists
drop table if exists task_trigger;

-- Create the task_trigger table
create table if not exists task_trigger
(
  id   timestamp primary key,
  type text check (type in ('dependency', 'event', 'mix')),
  info json
);

-- Create an index for the task_trigger table on the type column
create index if not exists task_trigger_type_idx on task_trigger (type);

-- Drop the existing task_after_effect table if it exists
drop table if exists task_after_effect;

-- Create the task_after_effect table
create table if not exists task_after_effect
(
  id   timestamp primary key,
  type text check (type = 'periodic'),
  info json
);

-- Create an index for the task_after_effect table on the type column
create index if not exists task_after_effect_type_idx on task_after_effect (type);

-- Drop the existing root_task table if it exists
drop table if exists root_task;

-- Create the root_task table
create table if not exists root_task
(
  id timestamp primary key
);

-- Drop the existing suspended_task table if it exists
drop table if exists suspended_task;

-- Create the suspended_task table
create table if not exists suspended_task
(
  id   timestamp primary key,
  type text,
  info json
);

-- Create an index for the suspended_task table on the type column
create index if not exists suspended_task_type_idx on suspended_task (type);

-- Drop the existing app_state table if it exists
drop table if exists app_state;

-- Create the app_state table
create table if not exists app_state
(
  id                integer primary key check (id = 0), -- 使用固定的ID保证只有一个记录
  root_task         timestamp, -- 根任务的ID
  now_viewing_task  timestamp, -- 当前查看的任务的ID
  now_selected_task timestamp  -- 当前选中的任务的ID
);

-- Insert the initial singleton record
insert into app_state (id, root_task, now_viewing_task, now_selected_task)
VALUES (0, NULL, NULL, NULL);

-- Drop the existing task_ui table if it exists
drop table if exists task_ui;

-- Create the task_ui table
create table if not exists task_ui
(
  task_id     timestamp primary key,
  position_x  integer,
  position_y  integer
);
