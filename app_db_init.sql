-- Drop the existing tasks table if it exists
drop table if exists tasks;

-- Create the updated tasks table
create table if not exists task
(
  id             integer primary key autoincrement,
  root_task      integer,
  name           text,
  goal           text,
  deadline       timestamp,
  in_work_time   boolean,
  status         integer,
  parent_task    integer
);

-- Create indices for the tasks table
create index if not exists task_id_idx on task (id);
create index if not exists task_root_task_idx on task (root_task);
-- create index if not exists tasks_name_idx on tasks (name);
insert into task (id, root_task, name, goal, deadline, in_work_time, status, parent_task)
values (0, -1, 'Overall', 'Good Game', 4102405199, 0, 0, -1);

-- Drop the existing task_relation table if it exists
drop table if exists task_relation;

-- Create the task_relation table
create table if not exists task_relation
(
  parent_task integer, -- the parent task id
  source integer, -- the source task id
  target integer,  -- the target task id
  primary key (source, target)
);

-- Create indices for the task_relation table
create index if not exists task_relation_source_idx on task_relation (source);
create index if not exists task_relation_target_idx on task_relation (target);
create index if not exists task_relation_parent_task_idx on task_relation (parent_task);

-- Drop the existing task_trigger table if it exists
drop table if exists task_trigger;

-- Create the task_trigger table
create table if not exists task_trigger
(
  id   integer,
  type integer,
  info json,
  primary key (id, type)
);

-- Create an index for the task_trigger table on the type column
create index if not exists task_trigger_type_idx on task_trigger (type);
create index if not exists task_trigger_id_idx on task_trigger (id);

-- Drop the existing task_after_effect table if it exists
drop table if exists task_after_effect;

-- Create the task_after_effect table
create table if not exists task_after_effect
(
  id   integer,
  type integer,
  info json,
  primary key (id, type)
);

-- Create an index for the task_after_effect table on the type column
create index if not exists task_after_effect_type_idx on task_after_effect (type);
create index if not exists task_after_effect_id_idx on task_after_effect (id);

-- Drop the existing root_task table if it exists
drop table if exists root_task;

-- Create the root_task table
create table if not exists root_task
(
  id integer primary key
);

-- Drop the existing suspended_task table if it exists
drop table if exists suspended_task;

-- Create the suspended_task table
create table if not exists suspended_task
(
  id   integer primary key,
  type integer,
  info json
);

-- Create an index for the suspended_task table on the type column
create index if not exists suspended_task_type_idx on suspended_task (type);

-- Drop the existing app_state table if it exists
drop table if exists app_state;

-- Create the app_state table
create table if not exists app_state
(
  id                integer primary key check (id = 0),
  root_task         integer,
  now_viewing_task  integer,
  now_selected_task integer,
  work_time         timestamp,
  now_is_work_time  boolean,
  now_doing_task    integer
);

-- Insert the initial singleton record
insert into app_state (id, root_task, now_viewing_task, now_selected_task, work_time, now_is_work_time, now_doing_task)
VALUES (0, 0, 0, -1, 0, 0, -1);

-- Drop the existing task_ui table if it exists
drop table if exists task_ui;

-- Create the task_ui table
create table if not exists task_ui
(
  id     integer primary key,
  parent_task integer,
  position_x  integer,
  position_y  integer
);
