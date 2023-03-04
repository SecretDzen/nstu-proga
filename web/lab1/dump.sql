--
-- PostgreSQL database dump
--

-- Dumped from database version 12.14 (Ubuntu 12.14-0ubuntu0.20.04.1)
-- Dumped by pg_dump version 12.14 (Ubuntu 12.14-0ubuntu0.20.04.1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: labs; Type: SCHEMA; Schema: -; Owner: ex4to
--

CREATE SCHEMA labs;


ALTER SCHEMA labs OWNER TO ex4to;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: courses; Type: TABLE; Schema: labs; Owner: ex4to
--

CREATE TABLE labs.courses (
    id integer NOT NULL,
    name text
);


ALTER TABLE labs.courses OWNER TO ex4to;

--
-- Name: courses_id_seq; Type: SEQUENCE; Schema: labs; Owner: ex4to
--

CREATE SEQUENCE labs.courses_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE labs.courses_id_seq OWNER TO ex4to;

--
-- Name: courses_id_seq; Type: SEQUENCE OWNED BY; Schema: labs; Owner: ex4to
--

ALTER SEQUENCE labs.courses_id_seq OWNED BY labs.courses.id;


--
-- Name: degree; Type: TABLE; Schema: labs; Owner: ex4to
--

CREATE TABLE labs.degree (
    id integer NOT NULL,
    name text
);


ALTER TABLE labs.degree OWNER TO ex4to;

--
-- Name: degree_id_seq; Type: SEQUENCE; Schema: labs; Owner: ex4to
--

CREATE SEQUENCE labs.degree_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE labs.degree_id_seq OWNER TO ex4to;

--
-- Name: degree_id_seq; Type: SEQUENCE OWNED BY; Schema: labs; Owner: ex4to
--

ALTER SEQUENCE labs.degree_id_seq OWNED BY labs.degree.id;


--
-- Name: position; Type: TABLE; Schema: labs; Owner: ex4to
--

CREATE TABLE labs."position" (
    id integer NOT NULL,
    name text
);


ALTER TABLE labs."position" OWNER TO ex4to;

--
-- Name: position_id_seq; Type: SEQUENCE; Schema: labs; Owner: ex4to
--

CREATE SEQUENCE labs.position_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE labs.position_id_seq OWNER TO ex4to;

--
-- Name: position_id_seq; Type: SEQUENCE OWNED BY; Schema: labs; Owner: ex4to
--

ALTER SEQUENCE labs.position_id_seq OWNED BY labs."position".id;


--
-- Name: teachers; Type: TABLE; Schema: labs; Owner: ex4to
--

CREATE TABLE labs.teachers (
    id integer NOT NULL,
    "position" integer,
    degree integer,
    courses integer,
    surname text,
    room_number integer
);


ALTER TABLE labs.teachers OWNER TO ex4to;

--
-- Name: teachers_id_seq; Type: SEQUENCE; Schema: labs; Owner: ex4to
--

CREATE SEQUENCE labs.teachers_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE labs.teachers_id_seq OWNER TO ex4to;

--
-- Name: teachers_id_seq; Type: SEQUENCE OWNED BY; Schema: labs; Owner: ex4to
--

ALTER SEQUENCE labs.teachers_id_seq OWNED BY labs.teachers.id;


--
-- Name: courses id; Type: DEFAULT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs.courses ALTER COLUMN id SET DEFAULT nextval('labs.courses_id_seq'::regclass);


--
-- Name: degree id; Type: DEFAULT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs.degree ALTER COLUMN id SET DEFAULT nextval('labs.degree_id_seq'::regclass);


--
-- Name: position id; Type: DEFAULT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs."position" ALTER COLUMN id SET DEFAULT nextval('labs.position_id_seq'::regclass);


--
-- Name: teachers id; Type: DEFAULT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs.teachers ALTER COLUMN id SET DEFAULT nextval('labs.teachers_id_seq'::regclass);


--
-- Data for Name: courses; Type: TABLE DATA; Schema: labs; Owner: ex4to
--

COPY labs.courses (id, name) FROM stdin;
1	Web
2	Client-Server
3	Compilers
4	Economy
5	Life Safety
\.


--
-- Data for Name: degree; Type: TABLE DATA; Schema: labs; Owner: ex4to
--

COPY labs.degree (id, name) FROM stdin;
1	Candidate
2	Doctor
\.


--
-- Data for Name: position; Type: TABLE DATA; Schema: labs; Owner: ex4to
--

COPY labs."position" (id, name) FROM stdin;
1	Aspirant
2	Professor
3	Teacher
4	High Teacher
\.


--
-- Data for Name: teachers; Type: TABLE DATA; Schema: labs; Owner: ex4to
--

COPY labs.teachers (id, "position", degree, courses, surname, room_number) FROM stdin;
1	1	1	1	Popov	412
2	2	2	2	Shatalov	138
3	3	1	3	Igenov	213
4	4	2	4	German	321
5	1	1	5	Kheynov	128
\.


--
-- Name: courses_id_seq; Type: SEQUENCE SET; Schema: labs; Owner: ex4to
--

SELECT pg_catalog.setval('labs.courses_id_seq', 5, true);


--
-- Name: degree_id_seq; Type: SEQUENCE SET; Schema: labs; Owner: ex4to
--

SELECT pg_catalog.setval('labs.degree_id_seq', 2, true);


--
-- Name: position_id_seq; Type: SEQUENCE SET; Schema: labs; Owner: ex4to
--

SELECT pg_catalog.setval('labs.position_id_seq', 4, true);


--
-- Name: teachers_id_seq; Type: SEQUENCE SET; Schema: labs; Owner: ex4to
--

SELECT pg_catalog.setval('labs.teachers_id_seq', 5, true);


--
-- Name: courses courses_name_key; Type: CONSTRAINT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs.courses
    ADD CONSTRAINT courses_name_key UNIQUE (name);


--
-- Name: courses courses_pkey; Type: CONSTRAINT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs.courses
    ADD CONSTRAINT courses_pkey PRIMARY KEY (id);


--
-- Name: degree degree_name_key; Type: CONSTRAINT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs.degree
    ADD CONSTRAINT degree_name_key UNIQUE (name);


--
-- Name: degree degree_pkey; Type: CONSTRAINT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs.degree
    ADD CONSTRAINT degree_pkey PRIMARY KEY (id);


--
-- Name: position position_name_key; Type: CONSTRAINT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs."position"
    ADD CONSTRAINT position_name_key UNIQUE (name);


--
-- Name: position position_pkey; Type: CONSTRAINT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs."position"
    ADD CONSTRAINT position_pkey PRIMARY KEY (id);


--
-- Name: teachers teachers_pkey; Type: CONSTRAINT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs.teachers
    ADD CONSTRAINT teachers_pkey PRIMARY KEY (id);


--
-- Name: teachers teachers_courses_fkey; Type: FK CONSTRAINT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs.teachers
    ADD CONSTRAINT teachers_courses_fkey FOREIGN KEY (courses) REFERENCES labs.courses(id);


--
-- Name: teachers teachers_degree_fkey; Type: FK CONSTRAINT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs.teachers
    ADD CONSTRAINT teachers_degree_fkey FOREIGN KEY (degree) REFERENCES labs.degree(id);


--
-- Name: teachers teachers_position_fkey; Type: FK CONSTRAINT; Schema: labs; Owner: ex4to
--

ALTER TABLE ONLY labs.teachers
    ADD CONSTRAINT teachers_position_fkey FOREIGN KEY ("position") REFERENCES labs."position"(id);


--
-- PostgreSQL database dump complete
--

