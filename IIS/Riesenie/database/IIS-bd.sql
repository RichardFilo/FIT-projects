#---CREATE DATABASE---
#CREATE DATABASE IIS_db

#---CLEAN DATABASE---
DROP TABLE _mod_req;
DROP TABLE _member_req;
DROP TABLE _rank;
DROP TABLE _post;
DROP TABLE _thread;
DROP TABLE _member;
DROP TABLE _group;
DROP TABLE _user;


#---CREATE ALL TABLES---

CREATE TABLE _user(
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    firstname VARCHAR(30) NOT NULL,
    lastname VARCHAR(30) NOT NULL,
    birthdate DATE NOT NULL,
    image LONGBLOB,
    email VARCHAR(50) NOT NULL,
    info VARCHAR(300),
    admin TINYINT(1) DEFAULT 0,
    reg_visib TINYINT(1) DEFAULT 0,
    unreg_visib TINYINT(1) DEFAULT 0,
    reg_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

CREATE TABLE _group(
    label VARCHAR(40)  PRIMARY KEY,
    info VARCHAR(300),
    image LONGBLOB,
    creator_id INT(6) UNSIGNED NOT NULL,
    member_visib TINYINT(1) DEFAULT 0,
    unreg_visib TINYINT(1) DEFAULT 0,
    reg_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

    FOREIGN KEY (creator_id)
        REFERENCES _user(id)
        ON UPDATE CASCADE 
        ON DELETE CASCADE 
);

CREATE TABLE _member(
    user_id INT(6) UNSIGNED NOT NULL,
    group_label VARCHAR(40) NOT NULL,
    moderator TINYINT(1) DEFAULT 0,

    PRIMARY KEY (user_id, group_label),
    FOREIGN KEY (user_id)
        REFERENCES _user(id)
        ON UPDATE CASCADE 
        ON DELETE CASCADE, 
    FOREIGN KEY (group_label)
        REFERENCES _group(label)
        ON UPDATE CASCADE 
        ON DELETE CASCADE
);

CREATE TABLE _thread(
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    subject VARCHAR(40) NOT NULL,
    creator_id INT(6) UNSIGNED NOT NULL,
    group_label VARCHAR(40) NOT NULL,
    reg_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    
    FOREIGN KEY (creator_id)
        REFERENCES _user(id)
        ON UPDATE CASCADE 
        ON DELETE CASCADE,
    FOREIGN KEY (group_label)
        REFERENCES _group(label)
        ON UPDATE CASCADE 
        ON DELETE CASCADE
);

CREATE TABLE _post(
    id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    thread_id INT(6) UNSIGNED NOT NULL,
    creator_id INT(6) UNSIGNED NOT NULL,
    content VARCHAR(400) NOT NULL,
    reg_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,

    FOREIGN KEY (creator_id)
        REFERENCES _user(id)
        ON UPDATE CASCADE 
        ON DELETE CASCADE,
    FOREIGN KEY (thread_id)
        REFERENCES _thread(id)
        ON UPDATE CASCADE 
        ON DELETE CASCADE
);

CREATE TABLE _rank(
    post_id INT(6) UNSIGNED NOT NULL,
    user_id INT(6) UNSIGNED NOT NULL,
    value TINYINT(2) NOT NULL,

    PRIMARY KEY (user_id, post_id),
    FOREIGN KEY (user_id)
        REFERENCES _user(id)
        ON UPDATE CASCADE 
        ON DELETE CASCADE,
    FOREIGN KEY (post_id)
        REFERENCES _post(id)
        ON UPDATE CASCADE 
        ON DELETE CASCADE
);

CREATE TABLE _member_req(
    user_id INT(6) UNSIGNED NOT NULL,
    group_label VARCHAR(40) NOT NULL,

    PRIMARY KEY (user_id, group_label),
    FOREIGN KEY (user_id)
        REFERENCES _user(id)
        ON UPDATE CASCADE 
        ON DELETE CASCADE,
    FOREIGN KEY (group_label)
        REFERENCES _group(label)
        ON UPDATE CASCADE 
        ON DELETE CASCADE
);

CREATE TABLE _mod_req(
    user_id INT(6) UNSIGNED NOT NULL,
    group_label VARCHAR(40) NOT NULL,
    
    PRIMARY KEY (user_id, group_label),
    FOREIGN KEY (user_id)
        REFERENCES _user(id)
        ON UPDATE CASCADE 
        ON DELETE CASCADE,
    FOREIGN KEY (group_label)
        REFERENCES _group(label)
        ON UPDATE CASCADE 
        ON DELETE CASCADE
);


#---INSERTIONS---

#to the user table
INSERT INTO _user ( firstname, lastname, birthdate, email, info, reg_visib) 
VALUES ("Richard", "Filo", "1999-04-12", "risso999@gmail.com", "Ja som proste najlepsi", 1);

INSERT INTO _user (firstname, lastname, birthdate, email, info, unreg_visib) 
VALUES ("Adam", "Barca", "1998-02-19", "gof1234@gmail.com", "Ja som druhy najlepsi", 1);

INSERT INTO _user (firstname, lastname, birthdate, email, info, unreg_visib) 
VALUES ("Roman", "Cech", "1999-04-30", "komanesta12@gmail.com", "Ja som treti najlepsi", 1);

#to the grop table
INSERT INTO _group (label, info, creator_id, member_visib) 
VALUES ("STO Kojatice", "Tato skupina je vytvorena pre clenov nasho stolnotenisoveho muzstva", 1, 1);

INSERT INTO _group (label, info, creator_id, member_visib, unreg_visib) 
VALUES ("FK Kojatice", "Tato skupina je vytvorena pre clenov nasho futbaloveho muzstva", 2, 1, 1);

#to the member table
INSERT INTO _member (user_id, group_label, moderator)
VALUES (1, "STO Kojatice", 1);

INSERT INTO _member (user_id, group_label, moderator)
VALUES (2, "FK Kojatice", 1);

INSERT INTO _member (user_id, group_label)
VALUES (1, "FK Kojatice");

INSERT INTO _member (user_id, group_label)
VALUES (2, "STO Kojatice");

#to the thread table
INSERT INTO _thread (subject, creator_id, group_label)
VALUES ("Prvy zapas kola dopadol 18:0", 1, "STO Kojatice");

INSERT INTO _thread (subject, creator_id, group_label)
VALUES ("Druhy zapas dopadol 10:8", 2, "STO Kojatice");

INSERT INTO _thread (subject, creator_id, group_label)
VALUES ("Prvy zapas kola dopadol 2:0", 2, "FK Kojatice");

INSERT INTO _thread (subject, creator_id, group_label)
VALUES ("Druhy zapas dopadol 0:3", 1, "FK Kojatice");

#to the post table
INSERT INTO _post (content, thread_id, creator_id)
VALUES ("To je super", 1, 2);

INSERT INTO _post (content, thread_id, creator_id)
VALUES ("Diky moc snazili sme sa", 1, 1);

INSERT INTO _post (content, thread_id, creator_id)
VALUES ("Mohlo to byt lepsie", 2, 1);

INSERT INTO _post (content, thread_id, creator_id)
VALUES ("Pekny zaciatok", 3, 1);

INSERT INTO _post (content, thread_id, creator_id)
VALUES ("To je ale skoda", 4, 2);

#to the rank table
INSERT INTO _rank (user_id, post_id, value)
VALUES (1, 1, -1);

INSERT INTO _rank (user_id, post_id, value)
VALUES (2, 1, -1);

INSERT INTO _rank (user_id, post_id, value)
VALUES (1, 2, 1);

#to the member_req table
INSERT INTO _member_req (group_label, user_id)
VALUES ("STO Kojatice", 3);

INSERT INTO _member_req (group_label, user_id)
VALUES ("FK Kojatice", 3);

#to the mod_req table
INSERT INTO _mod_req (group_label, user_id)
VALUES ("STO Kojatice", 2);

INSERT INTO _mod_req (group_label, user_id)
VALUES ("FK Kojatice", 1);


#---DELETE---
#DELETE FROM _user WHERE id=1;

#---SELECTS---

#label of groups where creator is Richard
SELECT label
FROM _user JOIN _group
ON _user.id = _group.creator_id
WHERE firstname="Richard";

#number of groups members
SELECT group_label, COUNT(*) "number of members"
FROM _member 
GROUP BY group_label;

#number of groups threads
SELECT group_label, COUNT(*) "number of threads"
FROM _thread 
GROUP BY group_label;

#list of groups
SELECT label group_name, firstname creatorFN, lastname creatorLN
FROM _user JOIN _group 
ON _user.id = _group.creator_id;

#list of threads
SELECT subject thread_subject, group_label thread_group, firstname creatorFN, lastname creatorLN
FROM _user JOIN _thread 
ON _user.id = _thread.creator_id;

#list of posts
SELECT content , subject post_thread, group_label post_group, firstname creatorFN, lastname creatorLN
FROM _user JOIN _post JOIN _thread
ON _user.id = _thread.creator_id AND _post.thread_id = _thread.id;

#ranking of posts
SELECT content post_content, SUM(value) raking 
FROM _user JOIN _post JOIN _thread LEFT JOIN _rank 
ON _user.id = _thread.creator_id AND _post.thread_id = _thread.id AND _post.id = _rank.post_id 
GROUP BY content
HAVING SUM(value) IS NOT NULL;

#list of member requests to group
SELECT group_label group_name, firstname creatorFN, lastname creatorLN
FROM _user JOIN _member_req 
ON _user.id = _member_req.user_id;

#list of mod requests to group
SELECT group_label group_name, firstname creatorFN, lastname creatorLN
FROM _user JOIN _mod_req 
ON _user.id = _mod_req.user_id;
