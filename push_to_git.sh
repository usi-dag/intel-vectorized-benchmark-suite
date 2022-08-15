echo "Push results to Git"
git pull
currentDate=`date +"%Y-%m-%d %T"`
git add .
git -c "user.name=DAG TOWER BOT" -c "user.email=dag@usi.ch" commit -m "$1"
git push
