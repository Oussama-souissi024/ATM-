# 💳 Application Console de Simulation de DAB en C++

## 🧾 Présentation

Ce projet est une application console développée en C++ simulant un Distributeur Automatique de Billets (DAB). Il met en œuvre des concepts de programmation orientée objet (POO) et utilise des fichiers texte pour la persistance des données, offrant ainsi une approche éducative pour comprendre les opérations bancaires de base sans recourir à une base de données externe.

## ✨ Fonctionnalités

- **Authentification sécurisée** : Système de connexion avec numéro de compte et code PIN
- **Retrait rapide** : Options prédéfinies pour retirer rapidement des montants courants (20, 50, 100, 200, etc.)
- **Retrait normal** : Possibilité de saisir un montant personnalisé (multiple de 5)
- **Dépôt d'argent** : Ajout de fonds au compte avec validation
- **Consultation de solde** : Vérification du solde actuel du compte
- **Gestion de session** : Option de déconnexion pour sécuriser l'accès

## 🗂️ Structure du Projet

- **ATM Bank.cpp** : Fichier principal contenant tout le code source de l'application
- **Clients.txt** : Fichier de stockage des données clients (numéro de compte, code PIN, nom, téléphone, solde)
- **ATM Bank.sln** : Solution Visual Studio pour le projet
- **Fichiers de projet Visual Studio** : Fichiers de configuration nécessaires (.vcxproj, .filters, etc.)

## 🚀 Démarrage

### Prérequis

- Microsoft Visual Studio (2019 ou plus récent recommandé)
- Compilateur C++ compatible avec C++11 ou supérieur

### Installation

1. Clonez le dépôt sur votre machine locale
   ```bash
   git clone https://github.com/Oussama-souissi024/ATM-.git
