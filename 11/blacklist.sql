USE blacklist;
DROP TABLE IF EXISTS access_log;
CREATE TABLE IF NOT EXISTS access_log (
    id          INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    accessed_at DATETIME NOT NULL,
    agent       VARCHAR(64) NOT NULL,
    ip          VARCHAR(255) NOT NULL
);

DROP TABLE IF EXISTS flag;
CREATE TABLE flag (
    `flag is here!!!` VARCHAR(255) NOT NULL PRIMARY KEY
);
INSERT INTO flag VALUES ('ADCTF_d0NT_Us3_Us3l3SS_8l4ckL1sT_WtF');
