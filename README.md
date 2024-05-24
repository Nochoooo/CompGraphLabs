# Проект 1. Essay-app
___
<div align="center">
    <img src="https://i.ibb.co/BrZf1MC/AESv2.jpg">
</div>

___
## Оглавление
<div style="line-height: 2;">
  <a href="https://github.com/Nochoooo/Essay_app/README.md#Описание-проекта">1. Описание проекта</a><br>
  <a href="https://github.com/Nochoooo/Essay_app/README.md#Основные-шаги">3. Основные шаги</a><br>
  <a href="https://github.com/Nochoooo/Essay_app/README.md#Условия-соревнования">4. Условия соревнования</a><br>
  <a href="https://github.com/Nochoooo/Essay_app/README.md#Метрика-качества">5. Метрика качества</a><br>
  <a href="https://github.com/Nochoooo/Essay_app/README.md#Информация-о-данных">6. Информация о данных</a><br>
  <a href="https://github.com/Nochoooo/Essay_app/README.md#Структура-проекта">7. Структура проекта</a><br>
  <a href="https://github.com/Nochoooo/Essay_app/README.md#Инструкции-по-запуску">8. Инструкции по запуску</a><br>
  <a href="https://github.com/Nochoooo/Essay_app/README.md#Результат">9. Результат</a>
</div>

### Описание проекта  
Цель проекта — разработать приложение и обучить модель для оценки студенческих эссе, что поможет сократить затраты и время, необходимые для их ручной проверки. Это приложение также предоставит учащимся возможность получать регулярную и своевременную обратную связь о качестве написанных эссе.

### Основные шаги  
1. Анализ имеющихся данных: Проведем небольшой анализ имеющихся данных для лучшего понимания их структуры, характеристик и особенностей.
2. Предобработка данных с использованием DebertaV3Preprocessor: Применим предварительную обработку к данным с помощью DebertaV3Preprocessor для подготовки данных к обучению модели.
3. Использование предобученной модели DeBERTa_v3: Обучим модель DeBERTa_v3 для выполнения задачи оценки студенческих эссе.
4. Разработка небольшого приложения на Flask: Создадим веб-приложение с использованием Flask для предоставления возможности пользователям загружать и оценивать эссе.
5. Развертывание созданного приложения в Kubernetes: Развернем наше приложение в контейнерном оркестраторе Kubernetes для обеспечения масштабируемости, отказоустойчивости и управления его жизненным циклом.


### Условия соревнования:
##### [Соревнование Learning Agency Lab - Automated Essay Scoring 2.0](https://www.kaggle.com/competitions/learning-agency-lab-automated-essay-scoring-2)
- 2 апреля 2024 г. начало соревнования
- 25 июня 2024 г. крайний срок подачи заявок и объединения команд
- 2 июля 2024 г. конец соревнования

### Метрика качества
Построенная модель будет оцениваться на основе квадратично взвешенного коэффициента Каппа (QWK), который измеряет соответствие между двумя результатами. Этот показатель обычно варьируется от 0 (случайное совпадение) до 1 (полное совпадение). Также эта метрика может принимать отрицательное значение в случае если согласие хуже чем случайное. Данная метрика обычно используется для оценки того, насколько хорошо совпадают результаты системы и эксперта при наличии упорядоченных категорий (оценок в нашем случае). На главной странице соревнования Kaggle можно посмотреть как вычисляется данная метрика.

### Информация о данных
Набор данных конкурса включает около 24000 аргументированных эссе, написанных студентами. Каждое эссе оценивалось по шкале от 1 до 6
[(критерии оценивания)](https://storage.googleapis.com/kaggle-forum-message-attachments/2733927/20538/Rubric_%20Holistic%20Essay%20Scoring.pdf)

### Структура проекта

```plaintext
Essay_app/                    # Корневой каталог вашего проекта
│
├── .kube/                    # Каталог содержит манифесты развертывания Kubernetes
│   ├── app_deploy.yaml       # Определяет конфигурацию для развертывания контейнера приложения
│   └── db_deploy.yaml        # Определяет конфигурацию для развертывания контейнера базы данных
│
├── essay-app/
│   ├── app.py                # Основной скрипт приложения
│   ├── database.py           # Скрипт для операций с базой данных
│   ├── model.py              # Скрипт для операций с моделью
│   ├── my_model.keras        # Файл предварительно обученной модели Keras
│   ├── Dockerfile            # Инструкции для создания образа
│   ├── requirements.txt      # Зависимости приложения
│   └── templates/            # Каталог содержит файлы шаблонов HTML для рендеринга веб-страниц
│       ├── index.html
│       └── view.html
│
├── data/                     # Каталог содержит данные, используемые для обучения и тестирования модели
│   ├── train.csv
│   ├── test.csv
│   └── sample_submission.csv  
│
└── README.md                 # Описание проекта
```
### Инструкции по запуску
Предварительные условия:
- Docker: убедитесь, что Docker установлен в вашей системе. Вы можете скачать его  [отсюда](https://www.docker.com/products/docker-desktop/)
- Kubernetes: вам необходим будет kubectl (для управления кластером) и minikube (кластер из одной ноды). Все это можно установить [отсюда](https://kubernetes.io/docs/home/)

Пошаговые инструкции:
1. Клонируйте репозиторий.
```bash
git clone https://github.com/Nochoooo/Essay_app.git
```
2. Создайте образ Docker.
```
docker build -t {имя пользователя docker hub}/essay-app:v1 {путь к Dockerfile}
```
&nbsp;&nbsp;&nbsp;<span style="font-size: 0.75em;"># В файле app_deploy.yaml вам необходимо будет изменить название образа на "image: {имя пользователя docker hub}/essay-app:v1".
</span>
&nbsp;&nbsp;&nbsp;<span style="font-size: 0.75em;"># Созданный image можно посмотреть с помощью команды: "docker images".
</span>

3. Запуште образ на Docker Hub.
```
docker push {имя пользователя docker hub}/essay-app:v1
```
4. Запустите кластер.
```
minikube start
```
&nbsp;&nbsp;&nbsp;<span style="font-size: 0.75em;"># Созданные сущности kubernetes можете посмотреть с помощью команды kubectl get all</span>
5. Примените манифесты Kubernetes.
```
kubectl apply -f {путь к папке .kube}
```
6. Убедитесь, что все сущности имеют статус Running.
```
kubectl get all
```
7. Установите соединение.
```
kubectl port-forward service/essay-app-service
```
6. Доступ к приложению.
Откройте веб-браузер и перейдите по адресу: http://localhost:8000

### Результат:
- Метрика QWK на kaggle = 0.75
- Используемая модель deberta_v3_base_en (12-слойная модель DeBERTaV3 с сохранением регистра, обучення на английской Википедии, BookCorpus и OpenWebText)
- [Мой ноутбук kaggle](https://www.kaggle.com/code/valerazv/automated-essay-scoring-2-0)