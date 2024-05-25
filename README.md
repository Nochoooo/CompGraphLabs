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
  <a href="https://github.com/Nochoooo/Essay_app/README.md#Результат">9. Результаты</a>
</div>

---
### Описание проекта  
Цель проекта — разработать приложение и обучить модель для оценки студенческих эссе, что поможет сократить затраты и время, необходимые для их ручной проверки. Это приложение также предоставит учащимся возможность получать регулярную и своевременную обратную связь о качестве написанных эссе.

### Основные шаги  
1. Анализ имеющихся данных: проведем небольшой анализ имеющихся данных для лучшего понимания их структуры, характеристик и особенностей.
2. Предобработка данных: применим предварительную обработку к данным с помощью DebertaV3Preprocessor для подготовки данных к обучению модели.
3. Использование предобученной модели DeBERTa_v3: обучим модель DeBERTa_v3 для выполнения задачи оценки студенческих эссе.
4. Разработка небольшого приложения на Flask: создадим веб-приложение с использованием Flask для предоставления возможности пользователям загружать и оценивать эссе.
5. Развертывание созданного приложения в Kubernetes: развернем наше приложение в контейнерном оркестраторе Kubernetes для обеспечения масштабируемости, отказоустойчивости и управления его жизненным циклом.


### Условия соревнования:
##### [Соревнование Learning Agency Lab - Automated Essay Scoring 2.0](https://www.kaggle.com/competitions/learning-agency-lab-automated-essay-scoring-2)
- 2 апреля 2024 г. начало соревнования
- 25 июня 2024 г. крайний срок подачи заявок и объединения команд
- 2 июля 2024 г. конец соревнования

### Метрика качества
Построенная модель будет оцениваться на основе квадратично взвешенного коэффициента Каппа (QWK), который измеряет соответствие между двумя результатами. Этот показатель обычно варьируется от 0 (случайное соответствие) до 1 (полное соответствие). Также эта метрика может принимать отрицательное значение в случае если соответствие хуже чем случайное. Данная метрика обычно используется для оценки того, насколько хорошо совпадают результаты системы и эксперта при наличии упорядоченных категорий (оценок в нашем случае). На главной странице соревнования Kaggle можно посмотреть как вычисляется данная метрика.

### Информация о данных
Набор данных конкурса включает около 24000 аргументированных эссе, написанных студентами. Каждое эссе оценивалось по шкале от 1 до 6
[(критерии оценивания)](https://storage.googleapis.com/kaggle-forum-message-attachments/2733927/20538/Rubric_%20Holistic%20Essay%20Scoring.pdf).
Всего нам доступно около 17000 строк.<br>
Пример данных:

| essay_id | full_text                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        | score |
|----------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------|
| 000d118  | Many people have cars where they live. They don't know that using a car can lead to accidents or health issues. In VAUBAN, Germany, 70% of families don't own cars, and 57% sold theirs to move there. Street parking, driveways, and home garages are forbidden. Cars are rare in Vauban. Car ownership is allowed, but parking is expensive ($40,000). Vauban's model is seen as "smart planning". It reduces greenhouse gas emissions and encourages walking and cycling. The Environmental Protection Agency in the US promotes "car reduced" communities... | 3     |
| 000fe60  | I am a NASA scientist discussing the "face" on Mars. There's no life on Mars, so the "face" can't be Martian. It's a landform, not a sculpture. NASA's solution to explore Venus is a blimp-like vehicle hovering above the surface, avoiding harsh conditions. We must study Venus for solutions. Despite challenges, curiosity drives us to explore...                                                                                                                                                                                                         | 3     |
| 001ab80  | People wish for futuristic technology seen in movies. New car technology promises convenience but raises safety and liability concerns. Driverless cars are not fully autonomous yet, and liability issues remain. Some argue for more sustainable transportation options...                                                                                                                                                                                                                                                                                     | 4     |
| 0033037  | The posibilty of a face reconizing computer would be very helpful for children or even adults. Its would be helpful in a ways of satifying our needs and why showing us thing that would make going on the internet better.I think that the face reconizing computer would be very reliable; because in the text its says " A class room computer could recognize when a student is confused or bored". And if the students is "confused and bored" then the students is not really learning anything, beacuse all children can\'t be taught the same way...     | 2     |
---
### Структура проекта

```plaintext
Essay_app/                    # Корневой каталог проекта
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
---
### Инструкции по запуску
Предварительные условия:
- Docker: убедитесь, что Docker установлен в вашей системе. Вы можете скачать его [отсюда](https://www.docker.com/products/docker-desktop/)
- Kubernetes: вам необходим будет kubectl (для управления кластером) и minikube (кластер из одной ноды). Все это можно скачать [отсюда](https://kubernetes.io/docs/home/)

Пошаговые инструкции:
1. Клонируйте репозиторий.
```bash
git clone https://github.com/Nochoooo/Essay_app.git
```
2. Создайте образ Docker.
```
docker build -t {имя пользователя docker hub}/essay-app:v1 {путь к Dockerfile}
```
&nbsp;&nbsp;&nbsp;<span style="font-size: 0.75em;"># В файле app_deploy.yaml вам необходимо будет изменить название образа на "image: {имя пользователя docker hub}/essay-app:v1".<br>
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
kubectl port-forward service/essay-app-service 8000:80
```
6. Доступ к приложению.
Откройте веб-браузер и перейдите по адресу: http://localhost:8000
---
### Технический стек

- <span style="font-family:Times New Roman; font-size:1.0em;">Python</span>
- <span style="font-family:Times New Roman; font-size:1.0em;">TensorFlow, Keras_nlp</span>
- <span style="font-family:Times New Roman; font-size:1.0em;">PostgreSQL</span>
- <span style="font-family:Times New Roman; font-size:1.0em;">Docker</span>
- <span style="font-family:Times New Roman; font-size:1.0em;">Kubernetes</span>
- <span style="font-family:Times New Roman; font-size:1.0em;">Flask</span>

---
### Результаты
- Метрика QWK на kaggle = 0.746
- Используемая модель [deberta_v3_base_en](https://huggingface.co/microsoft/deberta-v3-base) (12-слойная модель DeBERTaV3 с сохранением регистра, обучення на английской Википедии, BookCorpus и OpenWebText)
- [Мой ноутбук kaggle](https://www.kaggle.com/code/valerazv/automated-essay-scoring-2-0)
