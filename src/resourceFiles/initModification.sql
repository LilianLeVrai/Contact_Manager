CREATE TABLE Modification(
   idModification INTEGER,
   contentModified VARCHAR(250) NOT NULL,
   dateModification VARCHAR(16) NOT NULL,
   idTodo INTEGER,
   idInteraction INTEGER,
   idContact INTEGER,
   PRIMARY KEY(idModification),
   FOREIGN KEY (idTodo) REFERENCES Todo(idTodo),
   FOREIGN KEY (idInteraction) REFERENCES Interaction(idInteraction),
   FOREIGN KEY (idContact) REFERENCES Contact(idContact)
);
