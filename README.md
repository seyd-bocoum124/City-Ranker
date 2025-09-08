# City Ranker - Traitement de Données Géographiques

## 📋 Description

**City Ranker** est une application en C qui traite des fichiers de données géographiques pour classer et afficher les villes les plus peuplées du monde. Ce projet démontre des compétences avancées en programmation système et traitement de données.

## 🎯 Objectif

Analyser des jeux de données complexes contenant des informations sur les pays et les villes, puis afficher un classement des villes les plus peuplées selon le nombre spécifié par l'utilisateur.

## 📊 Sources de Données

Le programme utilise deux fichiers principaux :

### 1. countryInfo.txt
- Contient les informations sur les pays
- Format : données séparées par des tabulations
- Champs utilisés : code pays (ex: "FR", "US") et nom du pays

### 2. cities15000.txt  
- Contient les informations sur les villes de +15,000 habitants
- Format : données séparées par des tabulations
- Champs utilisés : nom ville, population, code pays

## ⚙️ Fonctionnalités Techniques

### Traitement des Données
- **Lecture et parsing** de fichiers texte volumineux
- **Extraction précise** des champs via séparation par tabulations
- **Association villes-pays** par codes de référence
- **Validation** et nettoyage des données

### Algorithmes
- **Tri rapide (quicksort)** implémenté manuellement
- Optimisé pour trier par population décroissante
- Gestion efficace de grandes collections de données

### Gestion d'Erreurs
- Validation des arguments en entrée
- Vérification de l'existence des fichiers
- Contrôle des valeurs numériques (1-5000 villes)
- Messages d'erreur explicites en français

## 🚀 Utilisation

```bash
# Compilation
gcc -o cityranker main.c

# Exécution
./cityranker [nombre_de_villes]

# Exemple : afficher les 20 villes les plus peuplées
./cityranker 20
```

