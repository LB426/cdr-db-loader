-- Table: axe

-- DROP TABLE axe;

CREATE TABLE axe
(
  n1 int4,
  n2 int4,
  n3 int4,
  n4 int8,
  n6 int8,
  n8 int4,
  n13 int4,
  n14 char(20),
  n16 int4,
  n17 int4,
  n18 int4,
  n19 int4,
  n20 int4,
  n21 char(28),
  n23 int4,
  n24 int4,
  n25 int4,
  n26 int4,
  n27 char(20),
  n28 int4,
  n29 char(20),
  n30 int4,
  n31 char(28),
  n32 int4,
  n33 char(20),
  n34 int4,
  n35 int4,
  n36 int4,
  n37 date,
  n40 time,
  n43 time,
  n44 time,
  n45 int4,
  n46 time,
  n47 int4,
  n48 int4,
  n49 int4,
  n50 int4,
  n51 int4,
  n52 int4,
  n53 int4,
  n54 int4,
  n57 int4,
  n58 int4,
  n59 int4,
  n60 int4,
  n61 int4,
  n62 int4,
  n63 int4,
  n64 int4,
  n66 char(1),
  n67 char(2),
  n68 char(3),
  n72 char(1),
  n76 char(15),
  n78 char(7),
  n80 char(7),
  n82 char(1),
  n83 char(1),
  n84 char(1),
  n85 char(2),
  n86 char(3),
  n87 char(3),
  n88 int4,
  n89 int8,
  n90 int8,
  n91 int4,
  n92 int4,
  n93 int4,
  n94 int8,
  n108 char(1),
  n109 char(1),
  n111 char(1),
  n112 date,
  n113 time,
  n114 char(5)
) 
WITH OIDS;
ALTER TABLE axe OWNER TO dba;
COMMENT ON COLUMN axe.n1 IS 'Record type';
COMMENT ON COLUMN axe.n2 IS 'Cause for output';
COMMENT ON COLUMN axe.n3 IS 'Record number ';
COMMENT ON COLUMN axe.n4 IS 'Call identification number ';
COMMENT ON COLUMN axe.n6 IS 'Record sequence number';
COMMENT ON COLUMN axe.n8 IS 'Output for subscriber';
COMMENT ON COLUMN axe.n13 IS 'Length indicator for A-subscriber number';
COMMENT ON COLUMN axe.n14 IS 'A-subscriber number, right justified';
COMMENT ON COLUMN axe.n16 IS 'A-category, right justified';
COMMENT ON COLUMN axe.n17 IS 'Type of A-subscriber number';
COMMENT ON COLUMN axe.n18 IS 'A-subscriber numbering plan indicator';
COMMENT ON COLUMN axe.n19 IS 'Type of A-subscriber';
COMMENT ON COLUMN axe.n20 IS 'Length indicator for B-subscriber number';
COMMENT ON COLUMN axe.n21 IS 'B-subscriber number, right justified';
COMMENT ON COLUMN axe.n23 IS 'B-category';
COMMENT ON COLUMN axe.n24 IS 'Type of B-subscriber number';
COMMENT ON COLUMN axe.n25 IS 'B-subscriber numbering plan indicator';
COMMENT ON COLUMN axe.n26 IS 'Length indicator for calling party number';
COMMENT ON COLUMN axe.n27 IS 'Calling party number';
COMMENT ON COLUMN axe.n28 IS 'Length indicator for redirecting number';
COMMENT ON COLUMN axe.n29 IS 'Redirecting number';
COMMENT ON COLUMN axe.n30 IS 'Length indicator for called party number';
COMMENT ON COLUMN axe.n31 IS 'Called party number';
COMMENT ON COLUMN axe.n32 IS 'Length indicator for originally called number';
COMMENT ON COLUMN axe.n33 IS 'Originally called number';
COMMENT ON COLUMN axe.n34 IS 'Fault code';
COMMENT ON COLUMN axe.n35 IS 'Call status';
COMMENT ON COLUMN axe.n36 IS 'Abnormal call release indicator';
COMMENT ON COLUMN axe.n37 IS 'Date for start of charging, USA format';
COMMENT ON COLUMN axe.n40 IS 'Time for start of charging (24-hour clock)';
COMMENT ON COLUMN axe.n43 IS 'Time for stop of charging (24-hour clock)';
COMMENT ON COLUMN axe.n44 IS 'Time from register seizure to start of charging';
COMMENT ON COLUMN axe.n45 IS 'Chargeable duration ';
COMMENT ON COLUMN axe.n46 IS 'Interruption time';
COMMENT ON COLUMN axe.n47 IS 'Charged party';
COMMENT ON COLUMN axe.n48 IS 'Immediate service indicator';
COMMENT ON COLUMN axe.n49 IS 'Price';
COMMENT ON COLUMN axe.n50 IS 'Pulse charging indicator';
COMMENT ON COLUMN axe.n51 IS 'Number of meter pulses';
COMMENT ON COLUMN axe.n52 IS 'Origin for charging';
COMMENT ON COLUMN axe.n53 IS 'Tariff class';
COMMENT ON COLUMN axe.n54 IS 'Tariff switching indicator';
COMMENT ON COLUMN axe.n57 IS 'Call attempt indicator';
COMMENT ON COLUMN axe.n58 IS 'Call attempt state';
COMMENT ON COLUMN axe.n59 IS 'Cause code';
COMMENT ON COLUMN axe.n60 IS 'Location code';
COMMENT ON COLUMN axe.n61 IS 'Type of called subscriber';
COMMENT ON COLUMN axe.n62 IS 'Type of signalling ';
COMMENT ON COLUMN axe.n63 IS 'Length indicator for abbreviated number';
COMMENT ON COLUMN axe.n64 IS 'Abbreviated number, right justified';
COMMENT ON COLUMN axe.n66 IS 'Result of subscriber service procedure';
COMMENT ON COLUMN axe.n67 IS 'Type of procedure';
COMMENT ON COLUMN axe.n68 IS 'Subscriber service indicator';
COMMENT ON COLUMN axe.n72 IS 'Conference call indicator';
COMMENT ON COLUMN axe.n76 IS 'Exchange identity, right justified';
COMMENT ON COLUMN axe.n78 IS 'Outgoing route, right justified';
COMMENT ON COLUMN axe.n80 IS 'Incoming route, right justified';
COMMENT ON COLUMN axe.n82 IS 'Incoming route, left justified';
COMMENT ON COLUMN axe.n83 IS 'Originating code';
COMMENT ON COLUMN axe.n84 IS 'Destination code';
COMMENT ON COLUMN axe.n85 IS 'Type of seizure';
COMMENT ON COLUMN axe.n86 IS 'Type of indicator';
COMMENT ON COLUMN axe.n87 IS 'Telecommunication service code';
COMMENT ON COLUMN axe.n88 IS 'Network conversion type';
COMMENT ON COLUMN axe.n89 IS 'Flexible counter 1';
COMMENT ON COLUMN axe.n90 IS 'Flexible counter 2';
COMMENT ON COLUMN axe.n91 IS 'Subscriber service for ISDN supplementary services';
COMMENT ON COLUMN axe.n92 IS 'End-to-end access data map';
COMMENT ON COLUMN axe.n93 IS 'End-to-end access data indicator';
COMMENT ON COLUMN axe.n94 IS 'Flexible counter 3';
COMMENT ON COLUMN axe.n108 IS 'Forced disconnection information ';
COMMENT ON COLUMN axe.n109 IS 'Carrier access code, right justified';
COMMENT ON COLUMN axe.n111 IS 'Presentation indicator';
COMMENT ON COLUMN axe.n112 IS 'Date of execution of command';
COMMENT ON COLUMN axe.n113 IS 'Time of execution of command';
COMMENT ON COLUMN axe.n114 IS 'Command name';
