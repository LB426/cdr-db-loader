CREATE DATABASE tariff
  WITH OWNER = dba
       ENCODING = 'WIN1251'
       TABLESPACE = tarification;

CREATE TABLE nec
(
  anomb varchar(15) NOT NULL,
  cata int2,
  bnomb varchar(32) NOT NULL,
  dt date NOT NULL,
  tm time NOT NULL,
  dur int4,
  incrt varchar(8),
  inccn int2,
  outrt varchar(8),
  outcn int2,
  chrgm int4,
  mbi int2,
  rate int2,
  calltp int2,
  svcat int2,
  --CONSTRAINT nec_pkey PRIMARY KEY (anomb, bnomb, dt, tm)
) 
WITH OIDS;
ALTER TABLE nec OWNER TO dba;

CREATE TABLE amalog
(
  fname varchar(64),
  firstrec timestamp,
  lastrec timestamp,
  "comment" varchar(32)
)
WITH OIDS;
ALTER TABLE amalog OWNER TO dba;

