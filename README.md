<<<<<<< HEAD
[![codamMeyer](https://circleci.com/gh/codamMeyer/minishell.svg?style=shield)](https://app.circleci.com/pipelines/github/codamMeyer/minishell?branch=main)

- [Minishell Project - Tutorial](#minishell-project---tutorial)
		- [How to work as a team](#how-to-work-as-a-team)
		- [What's Continuous Integration (CI) ?](#whats-continuous-integration-ci-)
		- [How to setup CircleCI Tool ?](#how-to-setup-circleci-tool-)

# Minishell Project - Tutorial
### How to work as a team


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
=======


>>>>>>> 49ffcbb3ed19e9062fe4249db53e523afd33eced
