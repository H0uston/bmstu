CREATE TABLE university
(
    id integer NOT NULL,
    name text NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE user_description
(
    id integer NOT NULL,
    name text NOT NULL,
    email text NOT NULL,
    password text NOT NULL,
    birthday date,
    role text NOT NULL,
    university integer REFERENCES university,

    PRIMARY KEY (id)
);



CREATE TABLE category
(
    id integer NOT NULL,
    name text NOT NULL,
    description text,

    PRIMARY KEY (id)
);

CREATE TABLE group_description
(
    id integer NOT NULL,
    name text NOT NULL,
    private boolean NOT NULL,
    group_category integer REFERENCES category,
    icon_path text,

    PRIMARY KEY (id)
);

CREATE TABLE files
(
    id integer NOT NULL,
    name text NOT NULL,
    path text NOT NULL,
    date_of_load date NOT NULL,
    owner integer NOT NULL REFERENCES user_description,
    group_id integer NOT NULL REFERENCES group_description,

    PRIMARY KEY (id)
);

CREATE TABLE request_list
(
    user_id integer NOT NULL REFERENCES user_description,
    group_id integer NOT NULL REFERENCES group_description,
    is_awaiting boolean NOT NULL,
    is_accepted boolean NOT NULL,
    is_denied boolean NOT NULL,

    PRIMARY KEY (user_id, group_id)
);

CREATE TABLE progress
(
    id integer NOT NULL,
    total_count_tasks integer NOT NULL,
    completed_tasks integer NOT NULL

    CHECK (total_count_tasks > 0),
    CHECK (completed_tasks > 0),
    PRIMARY KEY (id)
);

CREATE TABLE role
(
    id integer NOT NULL,
    name text NOT NULL,

    PRIMARY KEY (id)
);

CREATE TABLE participation
(
    user_id integer NOT NULL REFERENCES user_description,
    role integer NOT NULL REFERENCES role,
    group_id integer NOT NULL REFERENCES group_description,
    progress_id integer NOT NULL REFERENCES progress,

    PRIMARY KEY (user_id, group_id)
);

DROP TABLE user_description CASCADE;
DROP TABLE group_description CASCADE;
DROP TABLE category CASCADE;
DROP TABLE participation CASCADE;
DROP TABLE files CASCADE;
DROP TABLE university CASCADE;
DROP TABLE progress CASCADE;
DROP TABLE request_list CASCADE;