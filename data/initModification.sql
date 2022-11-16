CREATE TABLE Modification(
   idModification INTEGER,
   contentModified VARCHAR(150) NOT NULL,
   dateModification DATE NOT NULL,
   idTodo INTEGER,
   idInteraction INTEGER,
   idContact INTEGER,
   PRIMARY KEY(idModification),
   FOREIGN KEY(idTodo) REFERENCES Todo(idTodo),
   FOREIGN KEY(idInteraction) REFERENCES Interaction(idInteraction),
   FOREIGN KEY(idContact) REFERENCES Contact(idContact)
);
