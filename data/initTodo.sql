CREATE TABLE Todo(
   idTodo INT,
   content VARCHAR(150) NOT NULL,
   dateTodo DATE,
   idInteraction INT NOT NULL,
   PRIMARY KEY(idTodo),
   FOREIGN KEY(idInteraction) REFERENCES Interaction(idInteraction)
);
