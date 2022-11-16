CREATE TABLE Interaction(
   idInteraction INT,
   content VARCHAR(150) NOT NULL,
   dateCreation VARCHAR(10) NOT NULL,
   idContact INT NOT NULL,
   PRIMARY KEY(idInteraction),
   FOREIGN KEY(idContact) REFERENCES Contact(idContact)
);
