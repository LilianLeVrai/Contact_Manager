CREATE TABLE Modification(
   idModification Int,
   contentModified VARCHAR(150) NOT NULL,
   dateModification DATE NOT NULL,
   idTodo INT,
   idInteraction INT,
   idContact INT,
   PRIMARY KEY(idModification),
   FOREIGN KEY(idTodo) REFERENCES Todo(idTodo),
   FOREIGN KEY(idInteraction) REFERENCES Interaction(idInteraction),
   FOREIGN KEY(idContact) REFERENCES Contact(idContact)
);
