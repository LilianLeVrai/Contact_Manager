CREATE TABLE Interaction(
   idInteraction INTEGER,
   content VARCHAR(150) NOT NULL,
   dateCreation VARCHAR(10) NOT NULL,
   idContact INTEGER NOT NULL,
   PRIMARY KEY(idInteraction),
   FOREIGN KEY(idContact) REFERENCES Contact(idContact)
);
