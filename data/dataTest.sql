delete from Contact;
delete from Interaction;

insert into Contact(lastName, firstName, company, mail, phone, picture, dateCreation) values ('Manzano', 'Lilian', 'UB', 'lilian@mail.com', '06 12 34 56 78', '../img/defaultImg.jpg', '01/01/2021');
insert into Contact(lastName, firstName, company, mail, phone, picture, dateCreation) values ('Pere', 'Brandon', 'ufr sciences et techniques', 'brandon@ufr.fr', '06 87 65 43 21', '../img/defaultImg.jpg', '02/02/2022');
insert into Contact(lastName, firstName, company, mail, phone, picture, dateCreation) values ('nomRandom', 'prenomRandom', 'metierRandom', 'contact@random.com', '06 01 02 03 04', '../img/defaultImg.jpg', '03/03/2023');

insert into Interaction(content, dateCreation, idContact) values ('Interaction 1', '01/01/2020', 1);
insert into Interaction(content, dateCreation, idContact) values ('Interaction 2', '01/01/2020', 1);

insert into Interaction(content, dateCreation, idContact) values ('Interaction 3', '01/01/2020', 3);