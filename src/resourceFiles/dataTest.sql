delete from Modification;
delete from Contact;
delete from Interaction;
delete from Todo;

insert into Contact(lastName, firstName, company, mail, phone, picture, dateCreation) values ('Manzano', 'Lilian', 'UB', 'lilian@mail.com', '06 12 34 56 78', ':/resources/resourceFiles/defaultImg.png', '01/01/2022');
insert into Contact(lastName, firstName, company, mail, phone, picture, dateCreation) values ('Pere', 'Brandon', 'ufr sciences et techniques', 'brandon@ufr.fr', '06 87 65 43 21', ':/resources/resourceFiles/defaultImg.png', '01/06/2022');
insert into Contact(lastName, firstName, company, mail, phone, picture, dateCreation) values ('nomRandom', 'prenomRandom', 'metierRandom', 'contact@random.com', '06 01 02 03 04', ':/resources/resourceFiles/defaultImg.png', '01/12/2022');
insert into Contact(lastName, firstName, company, mail, phone, picture, dateCreation) values ('Pierre', 'Jean', 'entrepriseRandom', 'jean72@random.com', '06 45 02 03 04', ':/resources/resourceFiles/defaultImg.png', '01/10/2022');
insert into Contact(lastName, firstName, company, mail, phone, picture, dateCreation) values ('Dupont', 'Jean', 'entrepriseRandom', 'JP@random.fr', '06 72 02 03 04', ':/resources/resourceFiles/defaultImg.png', '01/09/2022');
insert into Contact(lastName, firstName, company, mail, phone, picture, dateCreation) values ('nomQuelquonque', 'Jean-Pierre', 'metierRandom', 'mail@rand.fr', '06 57 22 03 04', ':/resources/resourceFiles/defaultImg.png', '01/12/2022');

insert into Interaction(content, dateCreation, idContact) values ('Interaction 1 Lilian', '01/01/2022', 1);
insert into Interaction(content, dateCreation, idContact) values ('Interaction 2 Lilian', '01/01/2022', 1);
insert into Interaction(content, dateCreation, idContact) values ('Interaction 3 random', '01/01/2022', 3);
insert into Interaction(content, dateCreation, idContact) values ('note 1', '01/01/2022', 4);
insert into Interaction(content, dateCreation, idContact) values ('note 2', '01/01/2022', 5);
insert into Interaction(content, dateCreation, idContact) values ('note 3', '01/01/2022', 6);

insert into Todo(content, idInteraction) values ('rdv + appeler', 4);
insert into Todo(content, dateTodo, idInteraction) values ('rdv', '01/01/2023', 5);
insert into Todo(content, dateTodo, idInteraction) values ('appeler', '02/02/2023', 5);
insert into Todo(content, dateTodo, idInteraction) values ('rdv', '02/02/2024', 6);
