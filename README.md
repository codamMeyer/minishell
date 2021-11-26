[![codamMeyer](https://circleci.com/gh/codamMeyer/minishell.svg?style=shield)](https://app.circleci.com/pipelines/github/codamMeyer/minishell?branch=main)

- [Minishell Project - Tutorial](#minishell-project---tutorial)
    - [How to work as a team](#how-to-work-as-a-team)
    - [What is Trello?](#what-is-trello)
    - [What's Continuous Integration (CI) ?](#whats-continuous-integration-ci-)
    - [How to setup CircleCI Tool ?](#how-to-setup-circleci-tool-)
    - [How to organize your Project?](#how-to-organize-your-project)
    - [Draw!](#draw)

# Minishell Project - Tutorial
### How to work as a team

- Discuss about the project, organize the tasks, break the project into small pieces (We used Trello)
- Set up your repo, require Review to merge branch
- Choose a CI tool (we chose CircleCI)
- Start by pair programming a simple task

### What is Trello?
- Trello is a collaboration tool that organizes your projects into boards. In one glance, Trello tells you what's being worked on, who's working on what, and where something is in a process. Imagine a white board, filled with lists of sticky notes, with each note as a task for you and your team.

### What's Continuous Integration (CI) ?

![ci_flow](/images/ci_flow.png)

It is the practice of integrating changes from different developers in the team into a mainline as early as possible, in best cases several times a day. This makes sure the code individual developers work on doesn’t divert too much. When you combine the process with automated testing, continuous integration can enable your code to be dependable.

### How to setup CircleCI Tool ?

![ci_flow](/images/circleci/1.png)

1. In the root of your directory, run:
    ```bash
    mkdir .circleci
    cd .circleci
    touch config.yml
    ```
2. Copy the example bellow in your config.yml file:
    ```yaml
    version: 2

    jobs:
      build:
        docker:
          - image: "debian:buster"
        steps:
          - checkout
          - run:
              name: Install dependencies
              command: 'apt-get update && apt-get install -y gcc make python3 python3-pip'
          - run:
              name: Install dependencies Python
              command: 'pip3 install -U pip && pip3 install -U setuptools && pip3 install -U norminette'
          - run:
              name: Build
              command: 'echo Building'
          - run:
              name: Unit-Test
              command: "echo Unit-Test"
          - run:
              name: Integration-Test
              command: "echo Integration-Test"
          - run:
              name: Norminette Check
              command: "echo run norminette"
    ```

    Later you'll change the run steps to fit your needs. You will replace the echo command with the command you need for each process in your project.

3. Access [**circleci**](https://circleci.com/signup/) and sign up with your **github** account.
4. Click on **Projects**
5. Click on **Set Up project**
6. We already have a config file, so click on **skip this step**
7. Click on **Use Existing Config**
8. Click on **Start building**

### How to organize your Project?
- Name the features you will implement, break into small pieces.
- Always work in vertical slices, so you always have a working program.
  - Let's say EXIT without any argument is your first feature
  - Do the parser only to handle an input line "exit"
  - Write the dispatcher that only dispatchs "exit"
  - Inplement a simple command exit
  Now you're able to run your program and exit it.

![ci_flow](/images/vertical_slice.png)

### Draw!

![ci_flow](/diagrams_and_screenshots/general_functionality.png)
![ci_flow](/diagrams_and_screenshots/Multiple_processes_diagram.png)
![ci_flow](/diagrams_and_screenshots/redirection_diagram.png)


