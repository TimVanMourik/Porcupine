import subprocess
import argparse
import os

try:
    import awscli
except ImportError as e:
    print("You haven't installed awscli!"
          " Please install by 'pip install awscli'.")
    exit()

def query_latest_version(dataset):
    cmd = ['aws', 's3', 'ls', '--no-sign-request', 's3://openneuro/%s/' %
           dataset]
    result = subprocess.check_output(cmd)
    versions = [s.replace('/\\n', '').replace("'", '').strip()
                for s in str(result).split('PRE')[1:]]
    versions = [s.split('_R')[-1] for s in versions]
    latest_version = sorted(versions)[-1]
    print("Latest version for dataset %s is R%s" % (dataset, latest_version))
    return latest_version

if __name__ == '__main__':

    parser = argparse.ArgumentParser("Tool to download OpenFmri datasets")
    parser.add_argument('-d', dest='dataset', default='ds000222', type=str, help='Dataset number')
    parser.add_argument('-s', dest='subjects', type=str, help='Which subjects to download',
                        default='sub-*')
    parser.add_argument('-v', dest='version', type=str, help='Version of dataset')
    parser.add_argument('-o', dest='out', type=str, help='Output directory',
                        required=True)
    args = parser.parse_args()

    if not os.path.isdir(args.out):
        os.makedirs(args.out)

    if args.version is None:
        version = query_latest_version(args.dataset)
    else:
        version = args.version

    if args.subjects == 'sub-*':
        print("Downloading all subjects for dataset %s!" % args.dataset)
    else:
        print("Downloading subjects '%s' for dataset %s!" % (args.subjects,
                                                             args.dataset))

    data_dir = 's3://openneuro/%s/%s_R%s/uncompressed' % (args.dataset,
                                                          args.dataset,
                                                          version)
    cmd = 'aws s3 sync --no-sign-request --exclude "*" --include "%s" %s %s'
    cmd = cmd % (args.subjects, data_dir, args.out)
    res = subprocess.call(cmd, shell=True)

