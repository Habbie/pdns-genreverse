.load sqlitearpa.sqlext
BEGIN;
DELETE FROM generatedrecords;
INSERT INTO generatedrecords SELECT NULL, -1, arpaizev4(content), 'PTR', name, ttl, prio, change_date FROM realrecords WHERE type='A' AND mapreverse IS NOT NULL;
INSERT INTO generatedrecords SELECT NULL, -1, arpaizev6(content), 'PTR', name, ttl, prio, change_date FROM realrecords WHERE type='AAAA' AND mapreverse IS NOT NULL;
COMMIT;
