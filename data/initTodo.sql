CREATE TABLE Todo(
   idTodo INT,
   content VARCHAR(150) NOT NULL,
   dateTodo VARCHAR(10),
   idInteraction INT NOT NULL,
   PRIMARY KEY(idTodo),
   FOREIGN KEY(idInteraction) REFERENCES Interaction(idInteraction)
);
