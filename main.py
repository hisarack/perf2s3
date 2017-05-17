import boto3
import botocore
import datetime
import os
import config

os.environ['LC_ALL'] = 'en_US.UTF-8'

client = boto3.client(
    's3',
    aws_access_key_id=config.S3_ACCESS_KEY,
    aws_secret_access_key=config.S3_SECRET_KEY
)

try:
    os.remove(config.PERF_TMP_FILENAME)
except OSError:
    pass

try:
    os.system('/data/workspace/seq_learn/perf_collector/perf2s3/syst_smpl -e cpu-clock -p 50000')
    current_datetime = datetime.datetime.now()
    s3_object_name = '{}.csv'.format(current_datetime)
    with open(config.PERF_TMP_FILENAME, 'r') as f:
        data = f.read()
        client.put_object(
            Bucket=config.S3_BUCKET_NAME,
            Body=data,
            Key=s3_object_name
        )
except botocore.exceptions.ClientError as e:
    raise e

try:
    os.remove(config.PERF_TMP_FILENAME)
except OSError:
    pass
