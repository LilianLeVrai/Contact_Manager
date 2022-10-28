CREATE TABLE Contact(
   idContact INT,
   lastName VARCHAR(50) NOT NULL,
   firstName VARCHAR(50) NOT NULL,
   company VARCHAR(50) NOT NULL,
   mail VARCHAR(50) NOT NULL,
   phone VARCHAR(50) NOT NULL,
   picture VARCHAR(50) NOT NULL,
   dateCreation DATE NOT NULL,
   PRIMARY KEY(idContact)
);

CREATE TABLE Interaction(
   idInteraction INT,
   content VARCHAR(150) NOT NULL,
   dateCreation DATE NOT NULL,
   idContact INT NOT NULL,
   PRIMARY KEY(idInteraction),
   FOREIGN KEY(idContact) REFERENCES Contact(idContact)
);

CREATE TABLE Todo(
   idTodo INT,
   content VARCHAR(150) NOT NULL,
   dateTodo DATE NOT NULL,
   idInteraction INT NOT NULL,
   PRIMARY KEY(idTodo),
   FOREIGN KEY(idInteraction) REFERENCES Interaction(idInteraction)
);

CREATE TABLE Modification(
   idModification VARCHAR(50),
   contentModified VARCHAR(150) NOT NULL,
   dateModification DATE NOT NULL,
   idTodo INT NOT NULL,
   idInteraction INT NOT NULL,
   idContact INT NOT NULL,
   PRIMARY KEY(idModification),
   FOREIGN KEY(idTodo) REFERENCES Todo(idTodo),
   FOREIGN KEY(idInteraction) REFERENCES Interaction(idInteraction),
   FOREIGN KEY(idContact) REFERENCES Contact(idContact)
);
