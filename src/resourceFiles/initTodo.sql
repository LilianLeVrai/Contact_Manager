CREATE TABLE Todo(
   idTodo INTEGER,
   content VARCHAR(150) NOT NULL,
   dateTodo VARCHAR(10),
   idInteraction INTEGER NOT NULL,
   PRIMARY KEY(idTodo),
   FOREIGN KEY(idInteraction) REFERENCES Interaction(idInteraction) ON DELETE CASCADE
);
